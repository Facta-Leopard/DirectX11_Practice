#pragma once
#include "component.h"

class C_CameraComponent
    : public C_Component
{
public:
    C_CameraComponent();

protected:
    C_CameraComponent(const C_CameraComponent& _Origin);

public:
    virtual ~C_CameraComponent();

public:
    CLONE(C_CameraComponent)

    virtual void MF_Prepare() override;

    virtual void MF_ComponentTick() override;

    virtual C_CameraComponent* MF_GetMyself() override
    {
        return this;
    };
};

