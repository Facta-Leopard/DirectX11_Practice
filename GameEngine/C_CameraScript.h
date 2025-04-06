#pragma once
#include "C_ScriptComponent.h"
class C_CameraScript :
    public C_ScriptComponent
{
public:
    C_CameraScript();

protected:
    C_CameraScript(const C_CameraScript& _Origin);

public:
    ~C_CameraScript();

public:
    CLONE(C_CameraScript)

    virtual void MF_ScriptTick() override;


};