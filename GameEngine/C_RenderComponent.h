#pragma once
#include "C_Component.h"

class C_RenderComponent :
    public C_Component
{
public:
    C_RenderComponent(E_COMPONENT_TYPE _E_COMPONENT);

protected:
    C_RenderComponent(const C_RenderComponent& _Origin);

public:
    ~C_RenderComponent();

public:
    virtual C_RenderComponent* MF_Clone() = 0;              // Clone Function; Vertual

    virtual void MF_ComponentTick() = 0;                    // ComponentTick; Virtual
};