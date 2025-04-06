#pragma once
#include "C_ScriptComponent.h"
class C_StateScript :
    public C_ScriptComponent
{
public:
    C_StateScript();

protected:
    C_StateScript(const C_StateScript& _Origin);

public:
    ~C_StateScript();

public:
    CLONE(C_StateScript)

    virtual void MF_ScriptTick() override;

};

