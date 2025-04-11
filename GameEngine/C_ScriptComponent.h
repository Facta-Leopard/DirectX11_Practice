#pragma once
#include "C_Component.h"

#include "enum.h"

class C_ScriptComponent :
    public C_Component
{
public:
    C_ScriptComponent(E_SCRIPT_TYPE _ScrptType);

protected:
    C_ScriptComponent(const C_ScriptComponent& _Origin);    // 향후, 설계방식 변경 있을 시에는 복사 생성자를 막는 것이 좋을듯? 현재, 스크립트가 기능기반이지만, 매니저 형식이 아니라 별도로 객체에 붙히는 설계를 선택함

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

