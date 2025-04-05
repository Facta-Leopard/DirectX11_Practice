#pragma once
#include "C_Component.h"
class C_CameraComponent :
    public C_Component
{
public:
    C_CameraComponent();

protected:
    C_CameraComponent(const C_CameraComponent& _Origin);

public:
    ~C_CameraComponent();

public:
    CLONE(C_CameraComponent)
};

