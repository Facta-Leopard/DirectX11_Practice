#pragma once
#include "C_ScriptComponent.h"
class C_NPCScript :
    public C_ScriptComponent
{
public:
    C_NPCScript();

protected:
    C_NPCScript(const C_NPCScript& _Origin);

public:
    ~C_NPCScript();

public:
    CLONE(C_NPCScript)
};

