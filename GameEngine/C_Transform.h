#pragma once
#include "C_Component.h"
class C_Transform
    : public C_Component
{
public:
    C_Transform();

protected:
    C_Transform(const C_Transform& _Origin);

public:
    virtual ~C_Transform();

public:
    CLONE(C_Transform)

    virtual void MF_ComponentTick() override;

    virtual C_Transform* MF_GetMyself() override
    {
        return this;
    };
};

