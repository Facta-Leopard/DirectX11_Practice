#pragma once
#include "component.h"

class C_Collider2D
    : public C_Component
{
public:
    C_Collider2D();

protected:
    C_Collider2D(const C_Collider2D& _Origin);

public:
    ~C_Collider2D();

public:
    CLONE(C_Collider2D)

    virtual void MF_ComponentTick() override;

    virtual C_Collider2D* MF_GetMyself() override
    {
        return this;
    };
};

