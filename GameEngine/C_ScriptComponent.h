#pragma once
#include "C_Component.h"

#include "enum.h"

class C_ScriptComponent :
    public C_Component
{
public:
    C_ScriptComponent(E_SCRIPT_TYPE _ScrptType);

protected:
    C_ScriptComponent(const C_ScriptComponent& _Origin);

public:
    ~C_ScriptComponent();

protected:
    E_SCRIPT_TYPE               M_ScrptType;                // E_SCRIPT_TYPE

public:
    virtual C_ScriptComponent* MF_Clone() = 0;              // Clone Function; Virtual

    virtual void MF_ComponentTick() final {}                // 상속받은 작동함수 추상화 오버라이드 불능 설정

    virtual void MF_ComponentTickAfter() override {}        // 상속받은 작동함수 추상화 오버라이드 불능 설정

    virtual void MF_ScriptTick() = 0;                       // 상속받는 클래스의 작동함수 작성을 강제하기 위해서 추상화 설정

public:
    E_SCRIPT_TYPE MF_Get_ScriptType()                       // Getter; 유의! C_Object의 Template Function과 관련있으므로, 수정시 주의!
    {
        return M_ScrptType;
    }
};

