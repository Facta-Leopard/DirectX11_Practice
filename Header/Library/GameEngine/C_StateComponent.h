#pragma once
#include "C_Component.h"

#include "global.h"

class C_StateComponent :
    public C_Component
{
public:
    C_StateComponent();

    // 향후, 필요시 복사 생성자 관련 부분 재정의

public:
    ~C_StateComponent();

protected:
    // 삭제관련;
    bool                    M_IsDelete;                     // bool; 지워질 대상인지; 남은 시간이 음수가 되면 지워지는 것으로 함
    float                   M_TimeLeftToDelete;             // float; 지워지기까지 남은 시간; 0일 경우 작동하지 않는 것으로 하자

    // 죽었는지 상태 및 관리용 시간
    bool                    M_IsDie;                        // bool; 죽었는지; 향후, 죽었음에도 바로 다음 프레임에서 지워지는 것이 아닌 딜레이를 주기 위함
    float                   M_TimeLeftToDie;                // float; 죽기까지 남은 시간; 0일 경우 작동하지 않는 것으로 하자

    // 향후, 확장성을 위해 상태이상 요소를 넣으면 좋을 듯하고, 추가시 Getter랑 Setter 전용 함수를 포함시키는 것도 좋을 듯; 일단은 if + else if 구조로 만들었으나, 향후 플래그 방식으로 하는 것도 고려해보자

public:
    virtual void MF_Prepare() override;

    virtual void MF_ComponentTick() override;                           // Broad Phase; 상태변경까지 남은 시간 계산; 유의! 인자가 추가될 경우, 내용부분 추가할 것! 향후, 확장성에 따른 조건문 추가로 포함할 것

    virtual void MF_ComponentTickAfter() override;                      // Narrow Phase; 남은 시간에 따른 상태 변경; 유의! 인자가 추가될 경우, 내용부분 추가할 것! 향후, 확장성에 따른 조건문 추가로 포함할 것

public:
    inline bool MF_Get_IsDelete()                                       // Getter
    {
        return M_IsDelete;
    }

    inline bool MF_Get_IsDie()                                          // Getter
    {
        return M_IsDie;
    }

public:
    inline void MF_Set_IsDelete(bool _Bool)                             // Setter
    {
        M_IsDelete = _Bool;
    }

    inline void MF_Set_TimeLeftToDelete(float _RemainTime)              // Setter
    {
        M_TimeLeftToDelete = _RemainTime;
    }

    inline void MF_Set_IsDie(bool _Bool)                                // Setter
    {
        M_IsDie = _Bool;
    }

    inline void MF_Set_TimeLeftToDie(float _RemainTime)                 // Setter
    {
        M_TimeLeftToDie = _RemainTime;
    }

protected:
    void MF_Count_TimeLeft();                                           // 유의! 인자가 추가될 경우, 내용부분 추가할 것! 향후, 확장성에 따른 조건문 추가로 포함할 것

    void MF_Check_State();                                              // 유의! 인자가 추가될 경우, 내용부분 추가할 것! 향후, 확장성에 따른 조건문 추가로 포함할 것

};

