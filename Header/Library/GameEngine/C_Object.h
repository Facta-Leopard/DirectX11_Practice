#pragma once
#include "C_Entity.h"

#include "define.h"

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
    // 효율성을 위해 Heap으로 관리
    // Object

    
    // Component
    C_Component*                P_M_Component_s[_COMPONENT_END];             // C_Component*
    C_RenderComponent*          P_M_RenderComponent;                         // C_RenderComponent*

    C_ScriptComponent*                   P_M_Script_s[_SCRIPT_END];                   // C_Script*


public:
    CLONE(C_Object)



};

