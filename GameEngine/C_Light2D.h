#pragma once
#include "C_Component.h"

class C_Light2D
    : public C_Component
{
public:
    C_Light2D();

protected:
    C_Light2D(const C_Light2D& _Origin);

public:
    ~C_Light2D();

public:
    CLONE(C_Light2D)

    virtual void MF_Prepare() override;

    virtual void MF_ComponentTick() override;

    virtual void MF_ComponentTickAfter() override;

};

