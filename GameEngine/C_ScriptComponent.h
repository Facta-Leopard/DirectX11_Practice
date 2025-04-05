#pragma once
#include "C_Component.h"
class C_ScriptComponent :
    public C_Component
{
public:
    C_ScriptComponent();

protected:
    C_ScriptComponent(const C_ScriptComponent& _Origin);

public:
    ~C_ScriptComponent();

public:
    virtual C_ScriptComponent* MF_Clone() = 0;          // Clone Function; Virtual
};

