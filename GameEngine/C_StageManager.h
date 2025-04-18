#pragma once
#include "C_Singleton.h"

#include "C_Stage.h"

class C_StageManager :
    public C_Singleton<C_StageManager>
{
    SINGLE(C_StageManager)

private:
    C_Stage*                    P_M_CurrentStage;                   // 현재 선택된 레벨
    C_Stage*                    P_M_Stage_s[_STAGE_END];            // 모든 스테이지

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

    // 향후, 스테이지 체인지 부분 함수 만든 후에 테스크 관리자로 정의할 예정
    inline void MF_Set_MF_Get_CurrentStage(C_Stage* _Stage)
    {
        if (nullptr == _Stage)      // 방어코드
        {
            POPUP_DEBUG(L"nullptr == _Stage", L"in MF_Set_MF_Get_CurrentStage(), nullptr == _Stage")
        }
        // 향후, TaskManager로 정리

    }

public:
    // 향후, 에셋 정리 후 코드 정리

};

