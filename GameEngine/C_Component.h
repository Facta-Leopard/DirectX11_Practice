#pragma once

#include "C_Entity.h"
#include "C_Singleton.h"

#include "component.h"

class C_Component :
    public C_Entity
{
public:
    C_Component(E_COMPONENT_TYPE _E_COMPONENT);

protected:

    C_Component(const C_Component& _Origin);

public:
    ~C_Component();

protected:
    C_Object*                       P_M_OwnerObject;                // C_Object*; 컴포넌트가 속한 객체 대상을 알려주는 역할

    const E_COMPONENT_TYPE          L_M_ComponentType;              // const E_COMPONENT_TYPE; 본인이 무슨 타입이지 생성될 때 정해지도록 하기 위함

public:
    virtual C_Component* MF_Clone() = 0;                            // Clone Function; Virtual

public:
    // 향후, 클래스별 자동형변환 추가예정



};

