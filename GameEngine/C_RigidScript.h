#pragma once
#include "C_ScriptComponent.h"
class C_RigidScript :
    public C_ScriptComponent
{
public:
    C_RigidScript();

protected:
    C_RigidScript(const C_RigidScript& _Origin);

public:
    ~C_RigidScript();

public:
    CLONE(C_RigidScript)
};

