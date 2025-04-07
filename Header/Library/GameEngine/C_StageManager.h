#pragma once
#include "C_Singleton.h"

#include "C_Stage.h"

class C_StageManager :
    public C_Singleton<C_StageManager>
{
    SINGLE(C_StageManager)

public:
    C_Stage*                    P_M_CurrentStage;                   // ���� ���õ� ����

public:
    void Initialize();

    void Update();

public:
    C_Stage* MF_GetCurrentStage()
    {
        return P_M_CurrentStage;
    }
};

