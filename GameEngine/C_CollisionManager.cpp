#include "pch.h"
#include "C_CollisionManager.h"

C_CollisionManager::C_CollisionManager()
	: SDK_M_Group_s{}
    
    , STL_M_SDKIsCollision{}
    , SDK_M_BucketSize(4096)

    , E_M_ColliderType(_COLLIDER_3D_SAT_ON)
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

    // �浹ü ����� ��� �� ������ ĳ��
    E_M_ColliderType = P_T_CurrentStage->MF_Get_ColliderType();                 // ������� ���̱��

    C_Group* P_T_GroupA = P_T_CurrentStage->MF_Get_Groups(_GroupIndexB);
    C_Group* P_T_GroupB = P_T_CurrentStage->MF_Get_Groups(_GroupIndexB);

    const vector<C_Object*>& L_STL_P_T_ObjectA = P_T_GroupA->MF_Get_AllObjectFromGroup();
    const vector<C_Object*>& L_STL_P_T_ObjectB = P_T_GroupB->MF_Get_AllObjectFromGroup();

    for (size_t i = 0; i < L_STL_P_T_ObjectA.size(); ++i)
    {
        C_Collider2D* P_T_ColliderA = L_STL_P_T_ObjectA[i]->MF_Get_Collider2DComponent();
        if (nullptr == P_T_ColliderA)                                         // �����ȯ;
            continue;

        for (size_t j = 0; j < L_STL_P_T_ObjectB.size(); ++j)
        {
            C_Collider2D* P_T_ColliderB = L_STL_P_T_ObjectB[j]->MF_Get_Collider2DComponent();
            if (nullptr == P_T_ColliderB)
                continue;                                                     // �����ȯ;

            // unordered map�� �� Ű �� ����
            ULARGE_INTEGER T_CollisionKey;                                    // ����! ULARGE_INTEGER�� ���Ͽ� ����ü�̹Ƿ�, ���� ����� ���� �� �ڷ����� ULONGLONG���� �ؾ���

            //// �ؽ�ȭ; ó���� ������(64��Ʈ)�� 2��(128��Ʈ)�� �ؼ� ��ü �ؽ������� ������, ��ȿ�������� ���ݰ� �ٽ� ID�������� ��ȸ�� 
            DWORD T_DwordA = (DWORD)(P_T_ColliderA->MF_Get_EntityID());
            DWORD T_DwordB = (DWORD)(P_T_ColliderB->MF_Get_EntityID());

            // �ؽ�ȭ�� ���� �� ����
            if (T_DwordA > T_DwordB) std::swap(T_DwordA, T_DwordB);           // ����, ����ȭ�� �ȴٴ� �����Ͽ��� std::swap()�� ���� �Ͱ� �������� �ϴ� �Ͱ� ������尡 �� ���̰� ������, �Լ� ȣ�� ������ ���ִ� �͵� ����غ���

            // ����! ������ �� ��ü�� �ؽ������� �̿��Ϸ���, ũ�� ������ ���� ���� �� �� ������ ������ �ؾ����� �߰��� ���޾����Ƿ�, ��ü�� ID �� ������� �ٽ� ��ȸ
            T_CollisionKey.QuadPart = (((DWORD)T_DwordA) << 32) | ((DWORD)T_DwordB);   // ����! ULARGE_INTEGER�� ���� �ƴ� SDK ���Ͽ��̹Ƿ�, ���̳ʸ� �̵��Ϸ��� ULONGLONG �� �ڷ��� ���� �ڷ����� ULARGE_INTEGER.QuadPart�� �����Ͽ� �ٲٴ� ���� ����Ǿ�� ��

            // Ű ���� unordered map���� ã�� ������ ����
            unordered_map<ULONGLONG, bool>::iterator T_Iterator = STL_M_SDKIsCollision.find(T_CollisionKey.QuadPart);
            if (T_Iterator == STL_M_SDKIsCollision.end())
            {
                STL_M_SDKIsCollision.insert(make_pair(T_CollisionKey.QuadPart, false));
                T_Iterator = STL_M_SDKIsCollision.find(T_CollisionKey.QuadPart);
            }

            // ������ �������� �� Ȯ��
            bool T_IsDelete = L_STL_P_T_ObjectA[i]->MF_Get_StateComponent()->MF_Get_IsDelete() || L_STL_P_T_ObjectB[j]->MF_Get_StateComponent()->MF_Get_IsDelete();

            if (true == T_IsDelete)                                           // �����ȯ; ������ �����̸� ���� ����� �ʿ䰡 ����
            {
                continue;
            }

            // ���� �浹������ �ִ��� �� ����
            bool& R_T_WasOverlap = STL_M_SDKIsCollision[T_CollisionKey.QuadPart];      // ������带 ���̱� ���� �������� ���

            // �浹��� ���ȭ

            //// �߽��� ����� ����
            ////// �߽������� ���� ��ġ���� Ȯ��
            bool T_IsDistanceOverlap = MF_Check_DistanceBetweenCenters(P_T_ColliderA, P_T_ColliderB);

            if ((false == T_IsDistanceOverlap) && (_COLLIDER_3D_SAT_OFF == E_M_ColliderType))               // �����ȯ; �߽ɳ��� �Ÿ��� ��ġ�� �ʰ�, SAT ����尡 �������� �ʴٸ� ����� �ʿ䰡 ������, Narrow Phase�� ���� ������� ���ҽ�Ŵ; ����, �׳� ������ �ٷ� SAT�� ���� �ɼ��� �߰��ϴ� �͵� �����غ���
            {
                continue;
            }

            //// ����, �׷�Ÿ�� ���ǿ� ����, �����ȯ �ɾ������ �Ͱ�, SAT ���ο��� OBB�� ������ �ϴ� ���� �������� �����غ���
            if ((MF_Check_SAT(P_T_ColliderA, P_T_ColliderB)) && (true == R_T_WasOverlap))                   // �ڵ尳��; ����, �ٸ� ���ǿ����� �ִ��� �б⹮�� �ٿ��� �б⿹���� ������ �ϴ� ����� �߰��� ������ �� �ֵ��� ����
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
    switch (E_M_ColliderType)
    {
    case _COLLIDER_2D_SIDESCROLL_:
    case _COLLIDER_2D_TOPVEIW:
    case _COLLIDER_2D_ISOMETRICVIEW:

        Vector2 Vec2_T_PositionA = _ColliderA->MF_Get_ColliderPositionAsVector2();
        Vector2 Vec2_T_PositionB = _ColliderB->MF_Get_ColliderPositionAsVector2();

        Vector2 Vec2_T_RadiusA = _ColliderA->MF_Get_ColliderScale2D();
        Vector2 Vec2_T_RadiusB = _ColliderB->MF_Get_ColliderScale2D();

        if ((Vec2_T_PositionA - Vec2_T_PositionB).Length() < (Vec2_T_RadiusA.Length() - Vec2_T_RadiusB.Length()))
        {
            return true;
        }

        break;
    default:
        Vector3 Vec3_T_PositionA = _ColliderA->MF_Get_ColliderPositionAsVector3();
        Vector3 Vec3_T_PositionB = _ColliderB->MF_Get_ColliderPositionAsVector3();

        Vector3 Vec3_T_RadiusA = _ColliderA->MF_Get_ColliderScale3D();
        Vector3 Vec3_T_RadiusB = _ColliderB->MF_Get_ColliderScale3D();
        
        if ((Vec3_T_PositionA - Vec3_T_PositionB).Length() < (Vec3_T_RadiusA.Length() - Vec3_T_RadiusB.Length()))
        {
            return true;
        }

        break;
    }
    
    return false;
}


bool C_CollisionManager::MF_Check_SAT(C_Collider2D* _ColliderA, C_Collider2D* _ColliderB)
{
    return false;
}
