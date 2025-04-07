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

    virtual void MF_Prepare() override;

    virtual void MF_ScriptTick() override;
};

