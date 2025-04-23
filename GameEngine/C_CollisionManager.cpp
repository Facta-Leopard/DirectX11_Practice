#include "pch.h"
#include "C_CollisionManager.h"

C_CollisionManager::C_CollisionManager()
	: SDK_M_Group_s{}
    
    , STL_M_SDKIsCollision{}
{
	STL_M_SDKIsCollision.reserve(65535);    // 2^16 - 1; 멀티플랫폼 확장 고려 버킷;
}

C_CollisionManager::~C_CollisionManager()
{
}

// 정적변수 초기화
E_COLLIDER_TYPE C_CollisionManager::E_S_ColliderType(_COLLIDER_3D_SAT_ON);      // E_COLLIDER_TYPE; 충돌계산 오버헤드를 줄이기 위한 캐싱용

XMVECTOR C_CollisionManager::XM_VEC3_S_ColliderPositionA{};                         // Vector3; 충돌계산 오버헤드를 줄이기 위한 캐싱용
XMVECTOR C_CollisionManager::XM_VEC3_S_ColliderPositionB{};                         // Vector3; 충돌계산 오버헤드를 줄이기 위한 캐싱용

XMVECTOR C_CollisionManager::XM_VEC3_S_ColliderDistanceEachOther{};                 // Vector3; 충돌계산 오버헤드를 줄이기 위한 캐싱용

XMVECTOR C_CollisionManager::XM_VEC3_S_ColliderRadiusA{};                           // Vector3; 충돌계산 오버헤드를 줄이기 위한 캐싱용
XMVECTOR C_CollisionManager::XM_VEC3_S_ColliderRadiusB{};                           // Vector3; 충돌계산 오버헤드를 줄이기 위한 캐싱용

XMVECTOR C_CollisionManager::XM_VEC3_S_ColliderScaleA{};                            // Vector3; 충돌계산 오버헤드를 줄이기 위한 캐싱용
XMVECTOR C_CollisionManager::XM_VEC3_S_ColliderScaleB{};                            // Vector3; 충돌계산 오버헤드를 줄이기 위한 캐싱용

XMVECTOR C_CollisionManager::XM_VEC3_S_ColliderDirection_sA[_DIRECTION_END];        // Vector3; 충돌계산 오버헤드를 줄이기 위한 캐싱용
XMVECTOR C_CollisionManager::XM_VEC3_S_ColliderDirection_sB[_DIRECTION_END];        // Vector3; 충돌계산 오버헤드를 줄이기 위한 캐싱용

int C_CollisionManager::S_AxisCount;

HRESULT C_CollisionManager::MF_Initialize()
{
	return E_NOTIMPL;
}

void C_CollisionManager::MF_Update()
{
}

void C_CollisionManager::MF_Check_SameGroup(USHORT _GroupA, USHORT _GroupB)
{

}

void C_CollisionManager::MF_Check_OverlapGroup(E_GROUP_INDEX _GroupIndexA, E_GROUP_INDEX _GroupIndexB)
{
    C_Stage* P_T_CurrentStage = C_StageManager::SF_Get_Instance()->MF_Get_CurrentStage();

    // 충돌체 계산을 어떻게 할 것인지 캐싱
    E_S_ColliderType = P_T_CurrentStage->MF_Get_ColliderType();                 // 오버헤드 줄이기용

    C_Group* P_T_GroupA = P_T_CurrentStage->MF_Get_Group_s(_GroupIndexB);
    C_Group* P_T_GroupB = P_T_CurrentStage->MF_Get_Group_s(_GroupIndexB);

    const vector<C_Object*>& L_STL_P_T_ObjectA = P_T_GroupA->MF_Get_AllObjectFromGroup();
    const vector<C_Object*>& L_STL_P_T_ObjectB = P_T_GroupB->MF_Get_AllObjectFromGroup();

    for (size_t i = 0; i < L_STL_P_T_ObjectA.size(); ++i)
    {
        C_Collider2D* P_T_ColliderA = L_STL_P_T_ObjectA[i]->MF_Get_Collider2DComponent();
        if (nullptr == P_T_ColliderA)                                         // 조기반환;
            continue;

        for (size_t j = 0; j < L_STL_P_T_ObjectB.size(); ++j)
        {
            C_Collider2D* P_T_ColliderB = L_STL_P_T_ObjectB[j]->MF_Get_Collider2DComponent();
            if (nullptr == P_T_ColliderB)
                continue;                                                     // 조기반환;

            // unordered map에 쓸 키 값 생성
            ULARGE_INTEGER T_CollisionKey;                                    // 유의! ULARGE_INTEGER는 유니온 구조체이므로, 값을 사용할 때는 값 자료형인 ULONGLONG으로 해야함

            //// 해쉬화; 처음에 포인터(64비트)를 2개(128비트)로 해서 자체 해쉬값으로 쓰려다, 비효율적임을 깨닫고 다시 ID기준으로 선회함 
            //// 유의! DWORD로 하면 스왑에 따른 정렬과 시프트 이동에 문제가 생길 수 있고, 어차피 | 연산이므로 둘 다 유롱롱으로 하는 것이 로우레벨 최적화가 가능하다고 사료되어 코드개선했음
            //// 상기의 시행착오를 거친 흔적으로 Dword를 식별자 명칭으로 남겨두겠음!
            ULONGLONG T_DwordA = (ULONGLONG)(P_T_ColliderA->MF_Get_EntityID());
            ULONGLONG T_DwordB = (ULONGLONG)(P_T_ColliderB->MF_Get_EntityID());

            // 해쉬화를 위한 값 정렬
            if (T_DwordA > T_DwordB) std::swap(T_DwordA, T_DwordB);           // 향후, 최적화가 된다는 가정하에는 std::swap()을 쓰는 것과 수동으로 하는 것과 오버헤드가 별 차이가 없지만, 함수 호출 스택을 없애는 것도 고려해보자

            // 유의! 포인터 그 자체를 해쉬값으로 이용하려다, 크기 문제로 인해 더욱 더 더 복잡한 연산을 해야함을 중간에 깨달았으므로, 객체의 ID 값 붙히기로 다시 선회
            // 유의! 시프트 연산하면서 씹히는 비트를 생각하고, DWORD 자체가 32비트라 32비트 시프트하면 논리적 에러가 발생하므로 캐스팅 필요
            T_CollisionKey.QuadPart = ((T_DwordA) << 32) | T_DwordB;   // 유의! ULARGE_INTEGER는 값이 아닌 SDK 유니온이므로, 바이너리 이동하려면 ULONGLONG 인 자료형 값을 자료형인 ULARGE_INTEGER.QuadPart로 대입하여 바꾸는 것이 선행되어야 함

            // 키 값을 unordered map에서 찾고 없으면 넣음
            unordered_map<ULONGLONG, bool>::iterator T_Iterator = STL_M_SDKIsCollision.find(T_CollisionKey.QuadPart);
            if (T_Iterator == STL_M_SDKIsCollision.end())
            {
                STL_M_SDKIsCollision.insert(make_pair(T_CollisionKey.QuadPart, false));
                T_Iterator = STL_M_SDKIsCollision.find(T_CollisionKey.QuadPart);
            }

            //// 지워질 예정인지 값 확인
            //// 향후, 다시 생각해봐야 할 포인트는 오히려 오버헤드를 발생시키는 요인이 되고 있지 않은지?
            //bool T_IsDelete = L_STL_P_T_ObjectA[i]->MF_Get_StateComponent()->MF_Get_IsDelete() || L_STL_P_T_ObjectB[j]->MF_Get_StateComponent()->MF_Get_IsDelete();

            //if (true == T_IsDelete)                                           // 조기반환; 지워질 예정이면 굳이 계산할 필요가 없음
            //{
            //    continue;
            //}

            // 전에 충돌한적이 있는지 값 참조
            bool& R_T_WasOverlap = STL_M_SDKIsCollision[T_CollisionKey.QuadPart];      // 오버헤드를 줄이기 위해 참조형식 사용

            // 충돌계산 모듈화

            //// 중심점 계산방식 적용
            ////// 중심점끼리 계산시 겹치는지 확인
            bool T_IsDistanceOverlap = MF_Check_DistanceBetweenCenters(P_T_ColliderA, P_T_ColliderB);

            if ((false == T_IsDistanceOverlap) && (_COLLIDER_3D_SAT_OFF == E_S_ColliderType))               // 조기반환; 중심끼리 거리가 겹치지 않고, SAT 계산모드가 켜져있지 않다면 계산할 필요가 없으며, Narrow Phase를 통해 오버헤드 감소시킴; 향후, 그냥 무조건 바로 SAT로 가는 옵션을 추가하는 것도 생각해보자
            {
                continue;
            }

            //// 향후, 그룹타입 조건에 따라, 조기반환 걸어버리는 것과, SAT 내부에서 OBB를 순차로 하는 것이 좋을지도 생각해보자
            if ((true == MF_Check_SAT()) && (true == R_T_WasOverlap))                   // 코드개선; 향후, 다른 조건에서도 최대한 분기문을 줄여서 분기예측이 쉽도록 하는 방법을 추가로 적용할 수 있도록 하자
            {
                P_T_ColliderA->MF_On_OverlapIng(P_T_ColliderB);
                P_T_ColliderB->MF_On_OverlapIng(P_T_ColliderA);

            }
            else if (false == R_T_WasOverlap)
            {
                P_T_ColliderA->MF_On_OverlapBegin(P_T_ColliderB);
                P_T_ColliderB->MF_On_OverlapBegin(P_T_ColliderA);

                R_T_WasOverlap = true;
            }
            else
            {
                P_T_ColliderA->MF_On_OverlapEnd(P_T_ColliderB);
                P_T_ColliderB->MF_On_OverlapEnd(P_T_ColliderA);

                R_T_WasOverlap = false;
            }
        }
    }
}

bool C_CollisionManager::MF_Check_DistanceBetweenCenters(C_Collider2D* _ColliderA, C_Collider2D* _ColliderB)
{
    // 코드개선; 캐싱전용 멤버변수 이용; 각 요소들의 제곱값을 그대로 사용해서 루트계산의 연산 오버헤드 감소
    XM_VEC3_S_ColliderPositionA = _ColliderA->MF_Get_XMVECTOR3FromCollisionXMMATRIX();
    XM_VEC3_S_ColliderPositionB = _ColliderB->MF_Get_XMVECTOR3FromCollisionXMMATRIX();

    XM_VEC3_S_ColliderDistanceEachOther = XM_VEC3_S_ColliderPositionB - XM_VEC3_S_ColliderPositionA;
    float T_Distance = XMVectorGetX(XMVector3Length(XM_VEC3_S_ColliderDistanceEachOther));

    XM_VEC3_S_ColliderRadiusA = _ColliderA->MF_Get_ColliderScale();
    float T_RadiusA = XMVectorGetX(XMVector3Length(XM_VEC3_S_ColliderRadiusA));

    XM_VEC3_S_ColliderRadiusB = _ColliderB->MF_Get_ColliderScale();
    float T_RadiusB = XMVectorGetX(XMVector3Length(XM_VEC3_S_ColliderRadiusB));


    // 중심점과의 거리가 각 충돌체의 반지름의 합보다 작으면 충돌한 것으로 간주
    if (T_Distance < (T_RadiusA + T_RadiusB))
    {
        return true;
    }
    return false;
}


bool C_CollisionManager::MF_Check_SAT()
{
    switch (E_S_ColliderType)
    {
    case _COLLIDER_2D_SIDESCROLL_:		// Z 무효 (XY 평면 기준)
        S_AxisCount = 2;

        // 코드 개선; 오차 보정
        XM_VEC3_S_ColliderDirection_sA[_DIRECTION_RIGHT] = XMVectorSetZ(XM_VEC3_S_ColliderDirection_sA[_DIRECTION_RIGHT], 0.f);
        XM_VEC3_S_ColliderDirection_sA[_DIRECTION_RIGHT] = XMVector3Normalize(XM_VEC3_S_ColliderDirection_sA[_DIRECTION_RIGHT]);
        
        XM_VEC3_S_ColliderDirection_sA[_DIRECTION_UP]    = XMVectorSetZ(XM_VEC3_S_ColliderDirection_sA[_DIRECTION_UP], 0.f);
        XM_VEC3_S_ColliderDirection_sA[_DIRECTION_UP]    = XMVector3Normalize(XM_VEC3_S_ColliderDirection_sA[_DIRECTION_UP]);
        
        XM_VEC3_S_ColliderDirection_sA[_DIRECTION_FRONT] = XMVectorSetZ(XM_VEC3_S_ColliderDirection_sA[_DIRECTION_FRONT], 0.f);
        XM_VEC3_S_ColliderDirection_sA[_DIRECTION_FRONT] = XMVector3Normalize(XM_VEC3_S_ColliderDirection_sA[_DIRECTION_FRONT]);
        
        
        XM_VEC3_S_ColliderDirection_sB[_DIRECTION_RIGHT] = XMVectorSetZ(XM_VEC3_S_ColliderDirection_sB[_DIRECTION_RIGHT], 0.f);
        XM_VEC3_S_ColliderDirection_sB[_DIRECTION_RIGHT] = XMVector3Normalize(XM_VEC3_S_ColliderDirection_sB[_DIRECTION_RIGHT]);

        XM_VEC3_S_ColliderDirection_sB[_DIRECTION_UP]    = XMVectorSetZ(XM_VEC3_S_ColliderDirection_sB[_DIRECTION_UP], 0.f);
        XM_VEC3_S_ColliderDirection_sB[_DIRECTION_UP]    = XMVector3Normalize(XM_VEC3_S_ColliderDirection_sB[_DIRECTION_UP]);
        
        XM_VEC3_S_ColliderDirection_sB[_DIRECTION_FRONT] = XMVectorSetZ(XM_VEC3_S_ColliderDirection_sB[_DIRECTION_FRONT], 0.f);
        XM_VEC3_S_ColliderDirection_sB[_DIRECTION_FRONT] = XMVector3Normalize(XM_VEC3_S_ColliderDirection_sB[_DIRECTION_FRONT]);

        break;

    case _COLLIDER_2D_TOPVEIW:			// Y 무효 (XZ 평면 기준)
    case _COLLIDER_2D_ISOMETRICVIEW:
        S_AxisCount = 2;

        // 코드 개선; 오차 보정
        XM_VEC3_S_ColliderDirection_sA[_DIRECTION_RIGHT] = XMVectorSetY(XM_VEC3_S_ColliderDirection_sA[_DIRECTION_RIGHT], 0.f);
        XM_VEC3_S_ColliderDirection_sA[_DIRECTION_RIGHT] = XMVector3Normalize(XM_VEC3_S_ColliderDirection_sA[_DIRECTION_RIGHT]);

        XM_VEC3_S_ColliderDirection_sA[_DIRECTION_UP]    = XMVectorSetY(XM_VEC3_S_ColliderDirection_sA[_DIRECTION_UP], 0.f);
        XM_VEC3_S_ColliderDirection_sA[_DIRECTION_UP]    = XMVector3Normalize(XM_VEC3_S_ColliderDirection_sA[_DIRECTION_UP]);

        XM_VEC3_S_ColliderDirection_sA[_DIRECTION_FRONT] = XMVectorSetY(XM_VEC3_S_ColliderDirection_sA[_DIRECTION_FRONT], 0.f);
        XM_VEC3_S_ColliderDirection_sA[_DIRECTION_FRONT] = XMVector3Normalize(XM_VEC3_S_ColliderDirection_sA[_DIRECTION_FRONT]);


        XM_VEC3_S_ColliderDirection_sB[_DIRECTION_RIGHT] = XMVectorSetY(XM_VEC3_S_ColliderDirection_sB[_DIRECTION_RIGHT], 0.f);
        XM_VEC3_S_ColliderDirection_sB[_DIRECTION_RIGHT] = XMVector3Normalize(XM_VEC3_S_ColliderDirection_sB[_DIRECTION_RIGHT]);

        XM_VEC3_S_ColliderDirection_sB[_DIRECTION_UP]    = XMVectorSetY(XM_VEC3_S_ColliderDirection_sB[_DIRECTION_UP], 0.f);
        XM_VEC3_S_ColliderDirection_sB[_DIRECTION_UP]    = XMVector3Normalize(XM_VEC3_S_ColliderDirection_sB[_DIRECTION_UP]);

        XM_VEC3_S_ColliderDirection_sB[_DIRECTION_FRONT] = XMVectorSetY(XM_VEC3_S_ColliderDirection_sB[_DIRECTION_FRONT], 0.f);
        XM_VEC3_S_ColliderDirection_sB[_DIRECTION_FRONT] = XMVector3Normalize(XM_VEC3_S_ColliderDirection_sB[_DIRECTION_FRONT]);

        break;

    case _COLLIDER_3D_SAT_OFF:			// S.A.T 비활성화 (강제 false 반환)
        return false;

    case _COLLIDER_3D_SAT_ON:
    default:
        S_AxisCount = 3;
        break;
    }

    XMVECTOR XM_VEC3_T_Axis_s[15];
    int T_Index = 0;

    for (int i = 0; i < S_AxisCount; ++i)
    {
        XM_VEC3_T_Axis_s[T_Index++] = XM_VEC3_S_ColliderDirection_sA[i];
    }

    for (int i = 0; i < S_AxisCount; ++i)
    {
        XM_VEC3_T_Axis_s[T_Index++] = XM_VEC3_S_ColliderDirection_sB[i];
    }
        
    for (int i = 0; i < S_AxisCount; ++i)
    {
        for (int j = 0; j < S_AxisCount; ++j)
        {
            // XMVECTOR 외적
            XMVECTOR XM_VEC3_T_CrossValue = XMVector3Cross(XM_VEC3_S_ColliderDirection_sA[i], (XM_VEC3_S_ColliderDirection_sB[j]));

            // XMVECTOR 길이 계산 후 값 추출; 유의! 길이계산을 하면 XYZW 중 X에만 값이 대입됨!
            float T_CrollValueLength = XMVectorGetX(XMVector3Length(XM_VEC3_T_CrossValue));

            if (G_LL_ZeroScaleFloat < T_CrollValueLength)       // 방어코드; 유의! 제로스케일 값보다 작으면 무의미한 축이 되는 것이고 이를 계산에 넣지 않는다는 의미임! 코드 읽을 때 주의!
            {
                XM_VEC3_T_Axis_s[T_Index++] = XMVector3Normalize(XM_VEC3_T_CrossValue);
            }
        }
    }

    XM_VEC3_S_ColliderDistanceEachOther = XM_VEC3_S_ColliderPositionB - XM_VEC3_S_ColliderPositionA;

    float T_AbsoluteDistantEachOther = 0.f;

    for (int i = 0; i < T_Index; ++i)
    {
        const XMVECTOR& XM_VEC3_T_ProjAxis = XM_VEC3_T_Axis_s[i];

        float T_AbsoluteRadiusA = 0.f;
        for (int j = 0; j < S_AxisCount; ++j)

            T_AbsoluteRadiusA += fabs(XMVectorGetX(XMVector3Dot(XM_VEC3_T_ProjAxis, XM_VEC3_S_ColliderDirection_sA[j])));

        float T_AbsoluteRadiusB = 0.f;
        for (int j = 0; j < S_AxisCount; ++j)
            T_AbsoluteRadiusB += fabs(XMVectorGetX(XMVector3Dot(XM_VEC3_T_ProjAxis, XM_VEC3_S_ColliderDirection_sB[j])));


            T_AbsoluteDistantEachOther += fabs(XMVectorGetX(XMVector3Dot(XM_VEC3_T_ProjAxis, XM_VEC3_S_ColliderDistanceEachOther)));

        if (T_AbsoluteDistantEachOther > (T_AbsoluteRadiusA + T_AbsoluteRadiusB))
        {
            return false;
        }
    }

    // 모든 테스트를 다 통과하면, 투 충돌체는 겹쳐있다.
    return true;
}
