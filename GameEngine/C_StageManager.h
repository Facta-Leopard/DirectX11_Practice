#pragma once
#include "C_Singleton.h"

#include "C_Stage.h"

class C_StageManager :
    public C_Singleton<C_StageManager>
{
    SINGLE(C_StageManager)

private:
    C_Stage*                    P_M_CurrentStage;                   // ���� ���õ� ����
    C_Stage*                    P_M_Stage_s[_STAGE_END];            // ��� ��������

public:
    HRESULT MF_Initialize();

    void MF_Update();

public:
    inline C_Stage* MF_Get_CurrentStage()
    {
        return P_M_CurrentStage;
    }

    inline void MF_Set_CurrentStage(C_Stage* _Stage)
    {
        P_M_CurrentStage = _Stage;
    }

    // ����, �������� ü���� �κ� �Լ� ���� �Ŀ� �׽�ũ �����ڷ� ������ ����
    inline void MF_Set_MF_Get_CurrentStage(C_Stage* _Stage)
    {
        if (nullptr == _Stage)      // ����ڵ�
        {
            POPUP_DEBUG(L"nullptr == _Stage", L"in MF_Set_MF_Get_CurrentStage(), nullptr == _Stage")
        }
        // ����, TaskManager�� ����

    }

public:
    // ����, ���� ���� �� �ڵ� ����

};

