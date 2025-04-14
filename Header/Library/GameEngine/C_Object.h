#pragma once

#include "define.h"

#include "C_Entity.h"

class C_Component;
class C_Transform;
class C_Collider2D;
class C_StateComponent;
class C_Light2D;
class C_CameraComponent;

class C_RenderComponent;
class C_RenderComponent;
class C_RenderComponent;
class C_RenderComponent;
class C_RenderComponent;

class C_ScriptComponent;
class C_ScriptComponent;
class C_ScriptComponent;
class C_ScriptComponent;
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
    E_GROUP_INDEX                       M_GroupIndex;                                // E_GROUP_NUMBER; ������ ���� �׷��� ǥ��
    E_OBJECT_TYPE                       M_ObjectType;                                // E_OBJECT_TYPE; ���� �����ϴ� �κ����� �浹�κ��� ������ �˻縦 ���� ��; ����, �Һ�(const)�ϰ� �ϴ� �Ϳ� �����غ��� ���� ������

    // Object
    C_Object*                           M_ParentObejct;                              // C_Object*
    vector<C_Object*>                   STL_P_M_ChildObejct;                         // vector<C_Object*>


    // Component
    C_Component*                        P_M_Component_s[_COMPONENT_END];             // C_Component*
    C_RenderComponent*                  P_M_RenderComponent;                         // C_RenderComponent*; ����, �ڷ��� �������� �ؼ� ���ý����� �ϸ�, �߰��� Ȯ �ٲ�� �׷� ȿ���� �� �� ���� ������ ����غ���.

    C_ScriptComponent*                  P_M_Script_s[_SCRIPT_END];                   // C_Script*

public:
    CLONE(C_Object)

public:
    void MF_Prepare();                                                           // �ʱ�ȭ �Լ�; ��ݷ�Һ��� �غ�; C_Component -> C_ScriptComponent -> Obejct

    void MF_Tick();                                                              // Tick ��������; ����, Metal�� Compute Fragement�� �������ϴ� �͵� �����ϰ� ����

    void MF_TickAfter();                                                         // ��ó�� ���� Tick

    void MF_ChildTick();                                                         // �ڽĿ�����Ʈ tick() ����; �� ���� �Ʒ��� ����

    void MF_ComponentTick();                                                     // C_RenderComponent�� �۵���Ű�� ���� ����(��, ScriptComponent ����)

    void MF_ComponentTickAfter();                                                // C_RenderComponent�� �۵���Ű�� ���� ����(��, ScriptComponent ����)

    void MF_ScriptTick();                                                        // C_ScriptComponent�� �۵� ����

    void MF_Render();                                                            // Rendering ����; ������ ī�޶� ������Ʈ �� ī�޶� ������Ʈ �Լ��� �̿�

public:
    inline E_GROUP_INDEX MF_Get_GroupIndex()                                     // Getter; E_GROUP_TYPE�� enum������ ���δ� �׷� ��Ī�� ������ ������
    {
        return M_GroupIndex;
    }

    inline void MF_Set_GroupIndex(E_GROUP_INDEX _M_GroupIndex)                   // Setter
    {
        M_GroupIndex = _M_GroupIndex;
    }

    inline E_OBJECT_TYPE MF_Get_ObjectType()                                     // Getter
    {
        return M_ObjectType;
    }

    inline void MF_Set_ObjectType(E_OBJECT_TYPE _ObjectType)                     // Setter
    {
        M_ObjectType = _ObjectType;
    }

    inline C_Object* MF_Get_ParentObject()                                       // Getter
    {
        return M_ParentObejct;
    }

    inline vector<C_Object*> MF_Get_ChildObjects()                               // Getter
    {
        return STL_P_M_ChildObejct;
    }

    inline C_Component* MF_Get_Component(E_COMPONENT_TYPE _COMPONENTTYPE)        // Getter; ��ȯ���� ������ Down Casting �ؾ���; ����, Down Casting Automaically Logic ��������
    {
        return P_M_Component_s[_COMPONENTTYPE];
    }

    inline C_Transform* MF_Get_TransformComponent()
    {
        if (nullptr == P_M_Component_s[_COMPONENT_TRANSFORM])           // �����ȯ
        {
            POPUP_DEBUG(L"nullptr == P_M_Component_s[_COMPONENT_TRANSFORM]", L"in C_Transform* MF_Get_TransformComponent(), nullptr == P_M_Component_s[_COMPONENT_TRANSFORM]")
            return nullptr;
        }
        return (C_Transform*)P_M_Component_s[_COMPONENT_TRANSFORM];
    }

    inline C_Collider2D* MF_Get_Collider2DComponent()
    {
        if (nullptr == P_M_Component_s[_COMPONENT_COLLIDER2D])           // �����ȯ
        {
            POPUP_DEBUG(L"nullptr == P_M_Component_s[_COMPONENT_COLLIDER2D]", L"in C_Transform* MF_Get_Collider2DComponent(), nullptr == P_M_Component_s[_COMPONENT_COLLIDER2D]")
                return nullptr;
        }
        return (C_Collider2D*)P_M_Component_s[_COMPONENT_COLLIDER2D];
    }

    inline C_StateComponent* MF_Get_StateComponent()
    {
        if (nullptr == P_M_Component_s[_COMPONENT_STATE])           // �����ȯ
        {
            POPUP_DEBUG(L"nullptr == P_M_Component_s[_COMPONENT_STATE]", L"in C_Transform* MF_Get_StateComponent(), nullptr == P_M_Component_s[_COMPONENT_STATE]")
                return nullptr;
        }
        return (C_StateComponent*)P_M_Component_s[_COMPONENT_STATE];
    }

    inline C_Light2D* MF_Get_Light2DComponent()
    {
        if (nullptr == P_M_Component_s[_COMPONENT_LIGHT2D])           // �����ȯ
        {
            POPUP_DEBUG(L"nullptr == P_M_Component_s[_COMPONENT_LIGHT2D]", L"in C_Transform* MF_Get_Light2DComponent(), nullptr == P_M_Component_s[_COMPONENT_LIGHT2D]")
                return nullptr;
        }
        return (C_Light2D*)P_M_Component_s[_COMPONENT_LIGHT2D];
    }

    inline C_CameraComponent* MF_Get_CameraComponent()
    {
        if (nullptr == P_M_Component_s[_COMPONENT_CAMERA])           // �����ȯ
        {
            POPUP_DEBUG(L"nullptr == P_M_Component_s[_COMPONENT_CAMERA]", L"in C_Transform* MF_Get_CameraComponent(), nullptr == P_M_Component_s[_COMPONENT_CAMERA]")
                return nullptr;
        }
        return (C_CameraComponent*)P_M_Component_s[_COMPONENT_CAMERA];
    }

    inline C_RenderComponent* MF_Get_RenderComponent()                           // Getter; ���� C_Component�� C_ScriptComponet ����ó�� �ٲ��� ������ ���� ���� ������
    {
        if (nullptr == P_M_RenderComponent)           // �����ȯ
        {
            POPUP_DEBUG(L"nullptr == P_M_RenderComponent", L"in C_Transform* MF_Get_RenderComponent(), nullptr == P_M_RenderComponent")
                return nullptr;
        }
        return P_M_RenderComponent;
    }

    // ����, ���ҽ� ���� �ۼ��� ���� ������Ʈ ���� Ȯ��

    inline C_ScriptComponent* MF_Get_ScriptComponent(E_SCRIPT_TYPE _SCRIPTTYPE)  // Getter; ��ȯ���� ������ Down Casting �ؾ���; ����, Down Casting Automaically Logic ��������
    {
        if (nullptr == P_M_Script_s[_SCRIPTTYPE])           // �����ȯ
        {
            POPUP_DEBUG(L"nullptr == P_M_Script_s[_SCRIPTTYPE]", L"in C_Transform* MF_Get_ScriptComponent(), nullptr == P_M_Script_s[_SCRIPTTYPE]")
                return nullptr;
        }
        return P_M_Script_s[_SCRIPTTYPE];
    }

    // ����, ��ũ��Ʈ ���� �ۼ��� ���� ������Ʈ ���� Ȯ��

    // ��ϰ���
    //// Object ��ϰ���
    void MF_Attach_ObjectToParentObject(C_Object* _Object);                      // Attach; ������ ������Ʈ�� �θ������Ʈ�� ���

    void MF_Detach_MyselfFromParentObject();                                     // Detach; �θ������Ʈ���� �ڽ��� ��ϵ� ���� ����

    void MF_Attach_ObjectToChildObject(C_Object* _Object);                       // Attach; ������ ������Ʈ�� �ڽĿ�����Ʈ ��Ͽ� ���

    void MF_Detach_MyselfFromChildObject();                                      // Detach; �ڽĿ�����Ʈ�� ��ϵ� ������ �θ��� ���� ����

    void MF_Detach_DeadObjectFromChildObject();                                  // Detach; �ڽĿ�����Ʈ �� ���� �ڽ��� �����ϴ� �Լ�;

    //// Component ����
    void MF_Attach_Component(C_Component* _Component);                           // Attach; ������Ʈ ��� ���

    void MF_Detach_Component(C_Component* _Component);                           // Detach; ������Ʈ ��� ����




};