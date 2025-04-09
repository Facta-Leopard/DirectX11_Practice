#pragma once
#include "C_Singleton.h"

#include "C_Stage.h"

class C_StageManager :
    public C_Singleton<C_StageManager>
{
    SINGLE(C_StageManager)

public:
    C_Stage*                    P_M_CurrentStage;                   // 현재 선택된 레벨

public:
    HRESULT MF_Initialize();

    void MF_Update();

public:
    C_Stage* MF_Get_CurrentStage()
    {
        return P_M_CurrentStage;
    }

    // 향후, 스테이지 체인지 부분 함수 만든 후에 테스크 관리자로 정의할 예정
};

