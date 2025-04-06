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
};

