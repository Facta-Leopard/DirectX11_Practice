#pragma once

#include "C_Entity.h"
#include "C_Singleton.h"
class C_Component :
    public C_Entity
{
protected:
    C_Component();
    C_Component(const C_Component& _Origin);

    ~C_Component();
};

