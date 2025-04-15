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
        if (nullptr == P_T_ColliderA)                        // �����ȯ;
            continue;

        for (size_t j = 0; j < L_STL_P_T_ObjectB.size(); ++j)
        {
            C_Collider2D* P_T_ColliderB = L_STL_P_T_ObjectB[j]->MF_Get_Collider2DComponent();
            if (nullptr == P_T_ColliderB)
                continue;

            // unordered map�� �� Ű �� ����
            ULARGE_INTEGER T_CollisionKey;

            //// �ؽ�ȭ; ó���� ������(64��Ʈ)�� 2��(128��Ʈ)�� �ؼ� ��ü �ؽ������� ������, ��ȿ�������� ���ݰ� �ٽ� ID�������� ��ȸ�� 
            DWORD T_DwordA = (DWORD)(P_T_ColliderA->MF_Get_EntityID());
            DWORD T_DwordB = (DWORD)(P_T_ColliderB->MF_Get_EntityID());

            // �ؽ�ȭ�� ���� �� ����
            if (T_DwordA > T_DwordB) std::swap(T_DwordA, T_DwordB);   // ����, ����ȭ�� �ȴٴ� �����Ͽ��� std::swap()�� ���� �Ͱ� �������� �ϴ� �Ͱ� ������尡 �� ���̰� ������, �Լ� ȣ�� ������ ���ִ� �͵� ����غ���

            // ����! ������ �� ��ü�� �ؽ������� �̿��Ϸ���, ũ�� ������ ���� ���� �� �� ������ ������ �ؾ����� �߰��� ���޾����Ƿ�, ��ü�� ID �� ������� �ٽ� ��ȸ
            T_CollisionKey.QuadPart = (((DWORD)T_DwordA) << 32) | ((DWORD)T_DwordB);   // ����! ULARGE_INTEGER�� ���� �ƴ� SDK ���Ͽ��̹Ƿ�, ���̳ʸ� �̵��Ϸ��� ULONGLONG �� �ڷ��� ���� �ڷ����� ULARGE_INTEGER.QuadPart�� �����Ͽ� �ٲٴ� ���� ����Ǿ�� ��

            bool& bPrevOverlap = STL_M_SDKIsCollision[T_CollisionKey];
            bool T_IsDelete = L_STL_P_T_ObjectA[i]->MF_Get_StateComponent()->MF_Get_IsDelete() || L_STL_P_T_ObjectB[j]->MF_Get_StateComponent()->MF_Get_IsDelete();

            L_STL_P_T_ObjectA[i]->MF_Get_StateComponent()->MF_Get_IsDelete();

            // �浹��� ����ȭ �� ���ȭ
            //// �߽��� ����� ����


            //// ����, �׷�Ÿ�� ���ǿ� ����, �����ȯ �ɾ������ �Ͱ�, SAT ���ο��� OBB�� ������ �ϴ� ���� �������� �����غ���
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
