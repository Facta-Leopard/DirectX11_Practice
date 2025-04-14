#include "pch.h"
#include "C_CollisionManager.h"

C_CollisionManager::C_CollisionManager()
	: SDK_M_Group_s{}
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

    C_Group* P_T_GroupA = P_T_CurrentStage->MF_Get_Groups(_GroupIndexA);
    C_Group* P_T_GroupB = P_T_CurrentStage->GetLayer(_GroupB);

    const vector<C_Object*>& vecLeft = pLeftLayer->GetObjects();
    const vector<C_Object*>& vecRight = pRightLayer->GetObjects();

    for (size_t i = 0; i < vecLeft.size(); ++i)
    {
        C_Collider2D* pLeftCol = vecLeft[i]->Collider2D();
        if (!pLeftCol)
            continue;

        for (size_t j = 0; j < vecRight.size(); ++j)
        {
            C_Collider2D* pRightCol = vecRight[j]->Collider2D();
            if (!pRightCol)
                continue;

            // 충돌 키 생성
            uintptr_t a = reinterpret_cast<uintptr_t>(pLeftCol);
            uintptr_t b = reinterpret_cast<uintptr_t>(pRightCol);
            if (a > b) std::swap(a, b);
            DWORD_PTR collisionKey = (static_cast<DWORD_PTR>(a) << 32) | static_cast<DWORD_PTR>(b);

            bool& bPrevOverlap = m_mapInfo[collisionKey]; // 자동 삽입 + 참조
            bool bIsDead = vecLeft[i]->IsDead() || vecRight[j]->IsDead();

            if (IsOverlap(pLeftCol, pRightCol))
            {
                if (bPrevOverlap)
                {
                    if (bIsDead)
                    {
                        pLeftCol->EndOverlap(pRightCol);
                        pRightCol->EndOverlap(pLeftCol);
                    }
                    else
                    {
                        pLeftCol->Overlap(pRightCol);
                        pRightCol->Overlap(pLeftCol);
                    }
                }
                else
                {
                    if (!bIsDead)
                    {
                        pLeftCol->BeginOverlap(pRightCol);
                        pRightCol->BeginOverlap(pLeftCol);
                    }
                }

                bPrevOverlap = true;
            }
            else
            {
                if (bPrevOverlap)
                {
                    pLeftCol->EndOverlap(pRightCol);
                    pRightCol->EndOverlap(pLeftCol);
                }

                bPrevOverlap = false;
            }
        }
    }
}

void C_CollisionManager::MF_Check_SAT(C_Collider2D _ColliderA, C_Collider2D _ColliderB)
{

}
