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
    bool                                M_IsLive;                                   // bool; ������ �׾����� ����

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
    void MF_Prepare();                                                          // �ʱ�ȭ �Լ�; ��ݷ�Һ��� �غ�; C_Component -> C_ScriptComponent -> Obejct

    void MF_Tick();                                                             // Tick ��������; ����, Metal�� Compute Fragement�� �������ϴ� �͵� �����ϰ� ����

    void MF_TickAfter();                                                        // ��ó�� ���� Tick

    inline E_GROUP_TYPE MF_Get_GroupType()                                       // Getter
    {
        return M_GroupType;
    }

    inline void MF_Set_GroupIndex(E_GROUP_TYPE _GroupType)                       // Setter
    {
        M_GroupType = _GroupType;
    }

    inline C_Object* MF_Get_ParentObject()                                       // Getter
    {
        return M_ParentObejct;
    }

    inline C_Component* MF_Get_Component(E_COMPONENT_TYPE _COMPONENTTYPE)        // Getter; ��ȯ���� ������ Down Casting �ؾ���; ����, Down Casting Automaically Logic ��������
    {
        return P_M_Component_s[_COMPONENTTYPE];
    }

    inline C_RenderComponent* MF_Get_RenderComponent()                           // Getter; ���� C_Component�� C_ScriptComponet ����ó�� �ٲ��� ������ ���� ���� ������
    {
        return P_M_RenderComponent;
    }

    inline C_ScriptComponent* MF_Get_ScriptComponent(E_SCRIPT_TYPE _SCRIPTTYPE)  // Getter; ��ȯ���� ������ Down Casting �ؾ���; ����, Down Casting Automaically Logic ��������
    {
        return P_M_Script_s[_SCRIPTTYPE];
    }

    // ��ϰ���
    //// Object ��ϰ���
    void MF_Attach_ObjectToParentObject(C_Object* _Object);                      // Attach; ������ ������Ʈ�� �θ������Ʈ�� ���

    void MF_Detach_MyselfFromParentObject();                                     // Detach; �θ������Ʈ���� �ڽ��� ��ϵ� ���� ����

    void MF_Attach_ObjectToChildObject(C_Object* _Object);                       // Attach; ������ ������Ʈ�� �ڽĿ�����Ʈ ��Ͽ� ���

    void MF_Detach_MyselfFromChildObject();                                      // Detach; �ڽĿ�����Ʈ�� ��ϵ� ������ �θ��� ���� ����

    void MF_Detach_DeadObjectFromChildObject();                                  // Detach; �ڽĿ�����Ʈ �� ���� �ڽ��� �����ϴ� �Լ�;

    //// Component ����
    void MF_Attach_Component(C_Component* _Component);                           // Attach; ������Ʈ ��� ���

    //// 
    void MF_ChildTick();                                                        // �ڽĿ�����Ʈ tick() ����; �� ���� �Ʒ��� ����

    void MF_ComponentTick();                                                    // C_RenderComponent�� �۵���Ű�� ���� ����(��, ScriptComponent ����)

    void MF_ComponentTickAfter();                                               // C_RenderComponent�� �۵���Ű�� ���� ����(��, ScriptComponent ����)

    void MF_ScriptTick();                                                       // C_ScriptComponent�� �۵� ����

    void MF_Render();                                                           // Rendering ����; ������ ī�޶� ������Ʈ �� ī�޶� ������Ʈ �Լ��� �̿�

};

