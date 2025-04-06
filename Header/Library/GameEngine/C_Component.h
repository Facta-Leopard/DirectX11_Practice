#pragma once

#include "C_Entity.h"

class C_Component :
    public C_Entity
{
public:
    C_Component(E_COMPONENT_TYPE _E_COMPONENT);

protected:

    C_Component(const C_Component& _Origin);

public:
    virtual ~C_Component();

protected:
    C_Object*                       P_M_OwnerObject;                // C_Object*; 컴포넌트가 속한 객체 대상을 알려주는 역할

    const E_COMPONENT_TYPE          L_M_ComponentType;              // const E_COMPONENT_TYPE; 본인이 무슨 타입이지 생성될 때 정해지도록 하기 위함

public:
    // 추상 함수 설정한 클래스에서 상속받고 나서, 다시 추상클래스로 재정의할 때 override를 빼먹지 말자!
    virtual C_Component* MF_Clone() override = 0;                   // Clone Function; Virtual

public:
    // 향후, 클래스별 자동형변환 추가예정



};

