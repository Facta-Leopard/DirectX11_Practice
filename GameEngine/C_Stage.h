#pragma once
#include "C_Entity.h"
#include "C_Group.h"

class C_Stage :
    public C_Entity
{
public:
    C_Stage(E_STAGE_NUMBER _StageNumber);          // 스테이지 분류를 위함이므로, 생성시 강제하는 걸로

    // Stage를 복사할 일이 있을까? 복사생성자 정의가 필요하면 그 때 만드는 것으로 하자

public:
    ~C_Stage();

protected:
    const E_STAGE_NUMBER            L_M_StageNumber;                // E_STAGE_NUMBER; Stage 종류
    E_STAGE_STATE                   M_StageState;                   // E_STAGE_STATE; Play, Pause, Stop
    C_Group*                        P_M_Group_s[_GROUP_END];        // C_Group;

public:
    virtual C_Stage* MF_Clone() override final { return nullptr; }                      // 굳이, 쓸 일이 없을 것 같아서 사용 금지; 대입연산자를 굳이 막진 않음

public:
    void MF_Prepare();                                                                  // 초기화 함수

    void MF_Step();                                                                     // Group 내 모든 Object의 Tick() 실행

    void MF_StepAfter();                                                                // Group 내 모든 Object의 TickAfter() 실행

    void DetachGroups();                                                                // 소멸자 생성 이전 사용할 순환참조 방지용 함수


    inline E_STAGE_NUMBER MF_Get_StageNumber()                                          // Getter; 처음 만들어질 때 정해지는 부분이므로, Setter는 따로 지정하지 안음
    {
        return L_M_StageNumber;
    }

    inline E_STAGE_STATE MF_Get_StageState()                                            // Getter
    {
        return M_StageState;
    }

    inline void MF_Set_StageStage(E_STAGE_STATE _StageState)                            // Setter
    {
        M_StageState = _StageState;
    }


    inline C_Group* MF_Get_Groups()                                                     // Getter
    {
        return P_M_Group_s[_GROUP_END - 1];                                             // 향후, _GROUP_END - 1 부분 다시 생각해볼 것; Index를 벗어난 읽기 오류 디버깅
    }

    inline C_Group* MF_Set_GroupInGroups(C_Group* _Group, E_GROUP_TYPE _GroupType)      // Setter; 명명규칙에 벗어나지 않도록 헤더에 기재
    {
        for (size_t i = 0; i < _GROUP_END; i++)
        {
            if (_GroupType == i)
            {
                P_M_Group_s[i] = _Group;
            }
        }
    }

};

