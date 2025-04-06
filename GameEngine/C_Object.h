#pragma once

#include "define.h"

#include "C_Entity.h"

class C_Component;
class C_RenderComponent;
class C_ScriptComponent;

class C_Object :
    public C_Entity
{
protected:
    C_Object();
    C_Object(const C_Object& _Origin);
    
    ~C_Object();

protected:
    // 효율성을 위해 멤버들을 Heap으로 관리
    // 자기가 속한 부분을 표현하기 위함
    E_GROUP_NUMBER                      M_GroupIndex;                                // E_GROUP_NUMBER; 본인이 속한 그룹을 표시

    // Object

    
    // Component
    C_Component*                        P_M_Component_s[_COMPONENT_END];             // C_Component*
    C_RenderComponent*                  P_M_RenderComponent;                         // C_RenderComponent*

    C_ScriptComponent*                  P_M_Script_s[_SCRIPT_END];                   // C_Script*


public:
    CLONE(C_Object)

public:
    void MF_Prepare();

    void MF_Tick();                                     // Tick 구분이유; 향후, Metal의 Compute Fragement로 컨버전하는 것도 생각하고 있음

    void MF_ScriptTick();                               // C_ScriptComponent만 작동 목적

    void MF_ComponentTick();                            // C_RenderComponent를 작동시키기 위한 목적(단, ScriptComponent 제외)

};

