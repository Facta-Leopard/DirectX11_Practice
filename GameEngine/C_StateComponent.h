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
    // 삭제관련
    bool                    M_IsDelete;                     // bool; 지워질 대상인지
    float                   M_TimeLeftToDelete;             // float; 지워지기까지 남은 시간

    // 죽었는지 상태 및 관리용 시간
    bool                    M_IsDie;                        // bool; 죽었는지; 향후, 죽었음에도 바로 다음 프레임에서 지워지는 것이 아닌 딜레이를 주기 위함
    float                   M_TimeLeftToDie;                // float; 죽기까지 남은 시간

    // 향후, 확장성을 위해 상태이상 요소를 넣으면 좋을 듯

public:
    virtual void MF_Prepare() override;

    virtual void MF_ScriptTick() override;


};

