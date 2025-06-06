#pragma once
#include "C_Entity.h"
#include "C_Group.h"

class C_Stage :
    public C_Entity
{
public:
    C_Stage(E_STAGE_NUMBER _StageNumber);          // 스테이지 분류를 위함이므로, 생성시 강제하는 걸로

public:
    // 복사 생성자 안 만들었다가 디버깅 지옥에 빠졌었음 하 씨발..
    C_Stage(const C_Stage& _Origin);

public:
    ~C_Stage();

protected:
    const E_STAGE_NUMBER            L_E_M_StageNumber;                // E_STAGE_NUMBER; Stage 종류
    E_STAGE_STATE                   E_M_StageState;                   // E_STAGE_STATE; Play, Pause, Stop

    E_COLLIDER_TYPE                 E_M_ColliderType;                 // E_COLLIDER_TYPE; 유의! 충돌시스템 관련 가이드라인에 따라, 충돌계산 향상을 위한 추상적 선별 개념을 위해 쓰는 용도임

    C_Group*                        P_M_Group_s[_GROUP_END];          // C_Group*;

public:
    CLONE(C_Stage)

public:
    void MF_Prepare();                                                                  // 초기화 함수

    void MF_Step();                                                                     // Group 내 모든 Object의 Tick() 실행

    void MF_StepAfter();                                                                // Group 내 모든 Object의 TickAfter() 실행


public:
    inline E_STAGE_NUMBER MF_Get_StageNumber()                                          // Getter; 처음 만들어질 때 정해지는 부분이므로, Setter는 따로 지정하지 안음
    {
        return L_E_M_StageNumber;
    }

    inline E_STAGE_STATE MF_Get_StageState()                                            // Getter
    {
        return E_M_StageState;
    }

    inline E_COLLIDER_TYPE MF_Get_ColliderType()                                        // Getter
    {
        return E_M_ColliderType;
    }

    inline C_Group* MF_Get_Group_s(E_GROUP_INDEX _GroupIndex)                            // Getter
    {
        return P_M_Group_s[_GroupIndex];
    }

public:
    inline void MF_Set_StageState(E_STAGE_STATE _StageState)                            // Setter
    {
        E_M_StageState = _StageState;
    }

    inline C_Group* MF_Set_Group_s(E_GROUP_INDEX _GroupType, C_Group* _Group)     // Setter; 명명규칙에 벗어나지 않도록 헤더에 기재
    {
        if (nullptr == _Group)      // 방어코드
        {
            POPUP_DEBUG(L"nullptr == _Group", L"in C_Group* MF_Set_Group(), nullptr == _Group")
        }
        P_M_Group_s[_GroupType] = _Group;
    }

public:
    inline void MF_Detach_Group_s()                                                      // Detach; 소멸자 생성 이전 사용할 순환참조 방지용 함수
    {
        for (int i = 0; i < (int)_GROUP_END; ++i)
        {
            if (nullptr == P_M_Group_s[(E_GROUP_INDEX)i])				// 방어코드
            {
                continue;
            }
            P_M_Group_s[(E_GROUP_INDEX)i]->STL_P_M_AllObject.clear();
        }
    }


};

