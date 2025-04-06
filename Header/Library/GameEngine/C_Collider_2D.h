#pragma once
#include "component.h"

class C_Collider_2D
    : public C_Component
{
public:
    C_Collider_2D();

protected:
    C_Collider_2D(const C_Collider_2D& _Origin);

public:
    ~C_Collider_2D();

public:
    CLONE(C_Collider_2D)

    virtual void MF_ComponentTick() override;


};

