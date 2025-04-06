#pragma once
#include "C_Component.h"

class C_Light_2D
    : public C_Component
{
public:
    C_Light_2D();

protected:
    C_Light_2D(const C_Light_2D& _Origin);

public:
    ~C_Light_2D();

public:
    CLONE(C_Light_2D)
};

