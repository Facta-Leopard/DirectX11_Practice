#pragma once
#include "C_ScriptComponent.h"
class C_MoveScript :
    public C_ScriptComponent
{
public:
    C_MoveScript();

protected:
    C_MoveScript(const C_MoveScript& _Origin);

public:
    ~C_MoveScript();

public:
    CLONE(C_MoveScript)
};

