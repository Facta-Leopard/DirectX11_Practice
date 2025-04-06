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
    // ȿ������ ���� ������� Heap���� ����
    // �ڱⰡ ���� �κ��� ǥ���ϱ� ����
    E_GROUP_NUMBER                      M_GroupIndex;                                // E_GROUP_NUMBER; ������ ���� �׷��� ǥ��

    // Object

    
    // Component
    C_Component*                        P_M_Component_s[_COMPONENT_END];             // C_Component*
    C_RenderComponent*                  P_M_RenderComponent;                         // C_RenderComponent*

    C_ScriptComponent*                  P_M_Script_s[_SCRIPT_END];                   // C_Script*


public:
    CLONE(C_Object)

public:
    void MF_Prepare();

    void MF_Tick();                                     // Tick ��������; ����, Metal�� Compute Fragement�� �������ϴ� �͵� �����ϰ� ����

    void MF_ScriptTick();                               // C_ScriptComponent�� �۵� ����

    void MF_ComponentTick();                            // C_RenderComponent�� �۵���Ű�� ���� ����(��, ScriptComponent ����)

};

