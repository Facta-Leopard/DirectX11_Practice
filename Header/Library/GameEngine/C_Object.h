#pragma once

#include "define.h"

#include "C_Entity.h"

class C_Component;
class C_RenderComponent;
class C_ScriptComponent;

class C_Object :
    public C_Entity
{
public:
    C_Object();

protected:
    C_Object(const C_Object& _Origin);
    
public:
    ~C_Object();

protected:
    // ȿ������ ���� ������� Heap���� ����
    // Myself
    E_GROUP_TYPE                        M_GroupType;                                // E_GROUP_NUMBER; ������ ���� �׷��� ǥ��
    bool                                M_IsDead;                                   // bool; ������ �׾����� ����

    // Object
    C_Object*                           M_ParentObejct;                              // C_Object*
    vector<C_Object*>                   STL_M_ChildObejct;                           // vector<C_Object*>


    // Component
    C_Component*                        P_M_Component_s[_COMPONENT_END];             // C_Component*
    C_RenderComponent*                  P_M_RenderComponent;                         // C_RenderComponent*

    C_ScriptComponent*                  P_M_Script_s[_SCRIPT_END];                   // C_Script*


public:
    CLONE(C_Object)

public:
    void MF_Prepare();                                                  // �ʱ�ȭ �Լ�

    void MF_Tick();                                                     // Tick ��������; ����, Metal�� Compute Fragement�� �������ϴ� �͵� �����ϰ� ����

    void MF_ComponentTick();                                            // C_RenderComponent�� �۵���Ű�� ���� ����(��, ScriptComponent ����)

    void MF_ScriptTick();                                               // C_ScriptComponent�� �۵� ����

    void MF_Render();                                                   // Rendering ����; ������ ī�޶� ������Ʈ �� ī�޶� ������Ʈ �Լ��� �̿�


    inline E_GROUP_TYPE MF_GetGroupType()                               // Getter
    {
        return M_GroupType;
    }

    inline void MF_SetGroupIndex(E_GROUP_TYPE _GroupType)               // Setter
    {
        M_GroupType = _GroupType;
    }

    inline C_Object* MF_GetParentObject()                               // Getter
    {
        return M_ParentObejct;
    }

    // Object ����
    void MF_AttachObjectToParentObject(C_Object* _Object);              // Attach; ������ ������Ʈ�� �θ������Ʈ�� ���

    void MF_DetachMyselfFromParentObject();                             // Detach; �θ������Ʈ���� �ڽ��� ��ϵ� ���� ����


    void MF_AttachObjectToChildObject(C_Object* _Object);               // Attach; ������ ������Ʈ�� �ڽĿ�����Ʈ ��Ͽ� ���

    void MF_DetachMyselfFromChildObject();                              // Detach; �ڽĿ�����Ʈ�� ��ϵ� ������ �θ��� ���� ����

    // Component ����
    void MF_AttachComponent(C_Component* _Component);                   // Attach; ������Ʈ ��� ���

    // ����Լ�
    void MF_ChildTick();                                                // �ڽĿ�����Ʈ tick() ����; �� ���� �Ʒ��� ����

};

