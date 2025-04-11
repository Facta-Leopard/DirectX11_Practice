#pragma once
#include "C_ScriptComponent.h"
class C_FSMScript :
    public C_ScriptComponent
{
public:
    C_FSMScript();

protected:
    C_FSMScript(const C_FSMScript& _Origin);

public:
    ~C_FSMScript();

public:
    CLONE(C_FSMScript)

    virtual void MF_Prepare() override;

    virtual void MF_ScriptTick() override;

};

