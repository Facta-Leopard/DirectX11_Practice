#pragma once

#include "C_Entity.h"

#include "enum.h"
#include "component.h"

class C_Object;

class C_Component :
    public C_Entity
{
public:
    C_Component(E_COMPONENT_TYPE _E_COMPONENT);

protected:

    C_Component(const C_Component& _Origin);

public:
    virtual ~C_Component();                                 // 향후, 상호참조 문제는 없을 것으로 보이나 메모리 누수가 있는지 테스트 해보는 게 좋을 듯

protected:
    const E_COMPONENT_TYPE          L_M_ComponentType;              // const E_COMPONENT_TYPE; 본인이 무슨 타입인지 생성될 때 정해지도록 하기 위함

    C_Object*                       P_M_OwnerObject;                // C_Object*; 컴포넌트가 속한 객체 대상을 알려주는 역할

public:
    // 추상 함수 설정한 클래스에서 상속받고 나서, 다시 추상클래스로 재정의할 때 override를 빼먹지 말자!
    virtual C_Component* MF_Clone() override = 0;                   // Clone Function; Virtual

    virtual void MF_Prepare() = 0;                                  // 상속받는 클래스의 작동함수 작성을 강제하기 위해서 추상화 설정

    virtual void MF_ComponentTick() = 0;                            // 상속받는 클래스의 작동함수 작성을 강제하기 위해서 추상화 설정

    virtual void MF_ComponentTickAfter() = 0;                       // 상속받는 클래스의 작동함수 작성을 강제하기 위해서 추상화 설정

    virtual C_Component* MF_Get_ComponentMyself()                             // Return This Point By Vitual and Polymorph; 다형성을 이용한 자기자신 반환함수
    {
        if (_COMPONENT_SCRIPT == this->L_M_ComponentType)           // 방어코드
        {
            POPUP_DEBUG(L"Return This Is Script Component", L"in C_Component::GetMyself, _COMPONENT_SCRIPT == this->L_M_ComponentType")
        }
        if (_COMPONENT_RENDER == this->L_M_ComponentType)           // 방어코드
        {
            POPUP_DEBUG(L"Return This Is Render Component", L"in C_Component::GetMyself, _COMPONENT_RENDER == this->L_M_ComponentType")
        }
        return this; 
    }

public:
    inline E_COMPONENT_TYPE MF_Get_ComponentType()                  // Getter
    {
        return L_M_ComponentType;
    }

    inline C_Object* MF_Get_OwnerObject()                           // Getter
    {
        return P_M_OwnerObject;
    }
    // 향후, 다형성 이용을 고려하여 Save 및 Load 함수 적용하여야 함;



};

