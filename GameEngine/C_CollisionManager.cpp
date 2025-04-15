#include "pch.h"
#include "C_CollisionManager.h"

C_CollisionManager::C_CollisionManager()
	: SDK_M_Group_s{}
    , STL_M_SDKIsCollision{}
    , SDK_M_BucketSize(1024)
{
	size_t T_Resize= ((size_t)(_GROUP_END) * (size_t)(_GROUP_END));
	STL_M_SDKIsCollision.reserve(T_Resize);
}

C_CollisionManager::~C_CollisionManager()
{
}

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

    C_Group* P_T_GroupA = P_T_CurrentStage->MF_Get_Groups(_GroupIndexB);
    C_Group* P_T_GroupB = P_T_CurrentStage->MF_Get_Groups(_GroupIndexB);

    const vector<C_Object*>& L_STL_P_T_ObjectA = P_T_GroupA->MF_Get_AllObjectFromGroup();
    const vector<C_Object*>& L_STL_P_T_ObjectB = P_T_GroupB->MF_Get_AllObjectFromGroup();

    for (size_t i = 0; i < L_STL_P_T_ObjectA.size(); ++i)
    {
        C_Collider2D* P_T_ColliderA = L_STL_P_T_ObjectA[i]->MF_Get_Collider2DComponent();
        if (nullptr == P_T_ColliderA)                        // 조기반환;
            continue;

        for (size_t j = 0; j < L_STL_P_T_ObjectB.size(); ++j)
        {
            C_Collider2D* P_T_ColliderB = L_STL_P_T_ObjectB[j]->MF_Get_Collider2DComponent();
            if (nullptr == P_T_ColliderB)
                continue;

            // unordered map에 쓸 키 값 생성
            ULARGE_INTEGER T_CollisionKey;

            //// 해쉬화; 처음에 포인터(64비트)를 2개(128비트)로 해서 자체 해쉬값으로 쓰려다, 비효율적임을 깨닫고 다시 ID기준으로 선회함 
            DWORD T_DwordA = (DWORD)(P_T_ColliderA->MF_Get_EntityID());
            DWORD T_DwordB = (DWORD)(P_T_ColliderB->MF_Get_EntityID());

            // 해쉬화를 위한 값 정렬
            if (T_DwordA > T_DwordB) std::swap(T_DwordA, T_DwordB);   // 향후, 최적화가 된다는 가정하에는 std::swap()을 쓰는 것과 수동으로 하는 것과 오버헤드가 별 차이가 없지만, 함수 호출 스택을 없애는 것도 고려해보자

            // 유의! 포인터 그 자체를 해쉬값으로 이용하려다, 크기 문제로 인해 더욱 더 더 복잡한 연산을 해야함을 중간에 깨달았으므로, 객체의 ID 값 붙히기로 다시 선회
            T_CollisionKey.QuadPart = (((DWORD)T_DwordA) << 32) | ((DWORD)T_DwordB);   // 유의! ULARGE_INTEGER는 값이 아닌 SDK 유니온이므로, 바이너리 이동하려면 ULONGLONG 인 자료형 값을 자료형인 ULARGE_INTEGER.QuadPart로 대입하여 바꾸는 것이 선행되어야 함

            bool& bPrevOverlap = STL_M_SDKIsCollision[T_CollisionKey];
            bool T_IsDelete = L_STL_P_T_ObjectA[i]->MF_Get_StateComponent()->MF_Get_IsDelete() || L_STL_P_T_ObjectB[j]->MF_Get_StateComponent()->MF_Get_IsDelete();

            L_STL_P_T_ObjectA[i]->MF_Get_StateComponent()->MF_Get_IsDelete();

            // 충돌계산 최적화 및 모듈화
            //// 중심점 계산방식 적용


            //// 향후, 그룹타입 조건에 따라, 조기반환 걸어버리는 것과, SAT 내부에서 OBB를 순차로 하는 것이 좋을지도 생각해보자
            if (MF_Check_SAT(P_T_ColliderA, P_T_ColliderB))
            {
                if (bPrevOverlap)
                {
                    if (T_IsDelete)
                    {
                        P_T_ColliderA->MF_On_OverlapEnd(P_T_ColliderB);
                        P_T_ColliderB->MF_On_OverlapEnd(P_T_ColliderA);
                    }
                    else
                    {
                        P_T_ColliderA->MF_On_OverlapIng(P_T_ColliderB);
                        P_T_ColliderB->MF_On_OverlapIng(P_T_ColliderA);
                    }
                }
                else
                {
                    if (false == T_IsDelete)
                    {
                        P_T_ColliderA->MF_On_OverlapBegin(P_T_ColliderB);
                        P_T_ColliderB->MF_On_OverlapBegin(P_T_ColliderA);
                    }
                }

                bPrevOverlap = true;
            }
            else
            {
                if (bPrevOverlap)
                {
                    P_T_ColliderA->MF_On_OverlapEnd(P_T_ColliderB);
                    P_T_ColliderB->MF_On_OverlapEnd(P_T_ColliderA);
                }

                bPrevOverlap = false;
            }
        }
    }
}

void C_CollisionManager::MF_Check_SAT(C_Collider2D _ColliderA, C_Collider2D _ColliderB)
{

}
