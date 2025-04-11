#pragma once

#include "define.h"

#include "C_Entity.h"
#include "component.h"

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

    inline E_OBJECT_TYPE MF_Get_ObjectType()                                    // Getter
    {
        return M_ObjectType;
    }

    inline void MF_Set_ObjectType(E_OBJECT_TYPE _ObjectType)                    // Setter
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


    // Template Function ����
    //// �⺻ Template
    template <typename T_Template>
    T_Template* MF_Get_ComponentByReturnType()                                   // T_Template*; �⺻ ���ø�; ������� ������, �⺻������ ��
    {
        POPUP_DEBUG(L"Nullptr", L"in T_Template* MF_Get_ComponentByReturnType(), Nullptr")
        return nullptr;
    }

    //// C_Transform Ÿ�Կ� ���� Ư��ȭ
    template <>
    C_Transform* MF_Get_ComponentByReturnType<C_Transform>()                      // C_Transform*
    {
        if (nullptr == P_M_Component_s[_COMPONENT_TRANSFORM])               // ����ڵ�
        {
            POPUP_DEBUG(L"nullptr == P_M_Component_s[_COMPONENT_TRANSFORM]", L"in C_Transform* MF_Get_ComponentByReturnType<C_Transform>(), nullptr == P_M_Component_s[_COMPONENT_TRANSFORM]");
        }
        return (C_Transform*)P_M_Component_s[_COMPONENT_TRANSFORM];
    }

    //// C_Collider2D Ÿ�Կ� ���� Ư��ȭ
    template <>
    C_Collider2D* MF_Get_ComponentByReturnType<C_Collider2D>()                    // C_Collider2D*
    {
        if (nullptr == P_M_Component_s[_COMPONENT_COLLIDER_2D])             // ����ڵ�
        {
            POPUP_DEBUG(L"component", L"Failed");
        }
        return (C_Collider2D*)P_M_Component_s[_COMPONENT_COLLIDER_2D];
    }

    //// C_Light2D Ÿ�Կ� ���� Ư��ȭ
    template <>
    C_Light2D* MF_Get_ComponentByReturnType<C_Light2D>()                          // C_Light2D*
    {
        if (nullptr == P_M_Component_s[_COMPONENT_LIGHT_2D])                // ����ڵ�
        {
            POPUP_DEBUG(L"component", L"Failed");
        }
        return (C_Light2D*)P_M_Component_s[_COMPONENT_LIGHT_2D];
    }

    //// C_CameraComponent Ÿ�Կ� ���� Ư��ȭ
    template <>
    C_CameraComponent* MF_Get_ComponentByReturnType<C_CameraComponent>()          // C_CameraComponent*
    {
        if (nullptr == P_M_Component_s[_COMPONENT_CAMERA])                  // ����ڵ�
        {
            POPUP_DEBUG(L"component", L"Failed");
        }
        return (C_CameraComponent*)P_M_Component_s[_COMPONENT_CAMERA];
    }

    //// C_MeshRender Ÿ�Կ� ���� Ư��ȭ
    template <>
    C_MeshRender* MF_Get_ComponentByReturnType<C_MeshRender>()                    // C_MeshRender*
    {
        if (nullptr == P_M_Component_s[_COMPONENT_MESH_RENDER])             // ����ڵ�
        {
            POPUP_DEBUG(L"component", L"Failed");
        }
        return (C_MeshRender*)P_M_Component_s[_COMPONENT_MESH_RENDER];
    }

    //// C_SpriteRender Ÿ�Կ� ���� Ư��ȭ
    template <>
    C_SpriteRender* MF_Get_ComponentByReturnType<C_SpriteRender>()                // C_SpriteRender*
    {
        if (nullptr == P_M_Component_s[_COMPONENT_SPRITE_RENDER])           // ����ڵ�
        {
            POPUP_DEBUG(L"component", L"Failed");
        }
        return (C_SpriteRender*)P_M_Component_s[_COMPONENT_SPRITE_RENDER];
    }

    //// C_FlipbookRender Ÿ�Կ� ���� Ư��ȭ
    template <>
    C_FlipbookRender* MF_Get_ComponentByReturnType<C_FlipbookRender>()            // C_FlipbookRender*
    {
        if (nullptr == P_M_Component_s[_COMPONENT_FLIPBOOK_RENDER])         // ����ڵ�
        {
            POPUP_DEBUG(L"component", L"Failed");
        }
        return (C_FlipbookRender*)P_M_Component_s[_COMPONENT_FLIPBOOK_RENDER];
    }

    //// C_TileRender Ÿ�Կ� ���� Ư��ȭ
    template <>
    C_TileRender* MF_Get_ComponentByReturnType<C_TileRender>()                    // C_TileRender*
    {
        if (nullptr == P_M_Component_s[_COMPONENT_TILE_RENDER])             // ����ڵ�
        {
            POPUP_DEBUG(L"component", L"Failed");
        }
        return (C_TileRender*)P_M_Component_s[_COMPONENT_TILE_RENDER];
    }

    //// C_ParticleRender Ÿ�Կ� ���� Ư��ȭ
    template <>
    C_ParticleRender* MF_Get_ComponentByReturnType<C_ParticleRender>()            // C_ParticleRender*
    {
        if (nullptr == P_M_Component_s[_COMPONENT_PARTICLE_RENDER])         // ����ڵ�
        {
            POPUP_DEBUG(L"component", L"Failed");
        }
        return (C_ParticleRender*)P_M_Component_s[_COMPONENT_PARTICLE_RENDER];
    }

    //// C_RenderComponent Ÿ�Կ� ���� Ư��ȭ
    template <>
    C_RenderComponent* MF_Get_ComponentByReturnType<C_RenderComponent>()          // C_RenderComponent*
    {
        if (nullptr == P_M_RenderComponent)                                 // ����ڵ�
        {
            POPUP_DEBUG(L"nullptr == P_M_RenderComponent", L"in C_RenderComponent* MF_Get_ComponentByReturnType<C_RenderComponent>(), nullptr == P_M_RenderComponent");
        }
        return (C_RenderComponent*)P_M_RenderComponent;
    }

    //// C_ScriptComponent Ÿ�Կ� ���� Ư��ȭ
    ////// C_RigidScript Ÿ�Կ� ���� Ư��ȭ
    template <>
    C_RigidScript* MF_Get_ComponentByReturnType<C_RigidScript>()                  // C_RigidScript*
    {
        if (nullptr == P_M_Script_s[_SCRIPT_RIGID])                         // ����ڵ�
        {
            POPUP_DEBUG(L"nullptr == P_M_Script_s[_SCRIPT_RIGID]", L"in C_CameraScript* MF_Get_ComponentByReturnType<C_CameraScript>(), nullptr == P_M_Script_s[_SCRIPT_RIGID]");
        }

        E_SCRIPT_TYPE T_ScriptType = ((C_ScriptComponent*)P_M_Script_s[_SCRIPT_RIGID])->MF_Get_ScriptType();

        if (T_ScriptType != _SCRIPT_RIGID)                                  // ����ڵ�
        {
            POPUP_DEBUG(L"T_ScriptType != _SCRIPT_RIGID", L"in C_RigidScript* MF_Get_ComponentByReturnType<C_RigidScript>(), T_ScriptType != _SCRIPT_RIGID")
        }
        return (C_RigidScript*)P_M_Script_s[_SCRIPT_RIGID];
    }

    ////// C_StateScript Ÿ�Կ� ���� Ư��ȭ
    template <>
    C_StateScript* MF_Get_ComponentByReturnType<C_StateScript>()                  // C_StateScript*
    {
        if (nullptr == P_M_Script_s[_SCRIPT_STATE])                         // ����ڵ�
        {
            POPUP_DEBUG(L"nullptr == P_M_Script_s[_SCRIPT_STATE]", L"in C_CameraScript* MF_Get_ComponentByReturnType<C_CameraScript>(), nullptr == P_M_Script_s[_SCRIPT_STATE]");
        }

        E_SCRIPT_TYPE T_ScriptType = ((C_ScriptComponent*)P_M_Script_s[_SCRIPT_STATE])->MF_Get_ScriptType();

        if (T_ScriptType != _SCRIPT_STATE)                                  // ����ڵ�
        {
            POPUP_DEBUG(L"T_ScriptType != _SCRIPT_STATE", L"in C_StateScript* MF_Get_ComponentByReturnType<C_StateScript>(), T_ScriptType != _SCRIPT_STATE")
        }
        return (C_StateScript*)P_M_Script_s[_SCRIPT_STATE];
    }

    ////// C_MoveScript Ÿ�Կ� ���� Ư��ȭ
    template <>
    C_MoveScript* MF_Get_ComponentByReturnType<C_MoveScript>()                    // C_MoveScript*
    {
        if (nullptr == P_M_Script_s[_SCRIPT_MOVE])                          // ����ڵ�
        {
            POPUP_DEBUG(L"nullptr == P_M_Script_s[_SCRIPT_MOVE]", L"in C_CameraScript* MF_Get_ComponentByReturnType<C_CameraScript>(), nullptr == P_M_Script_s[_SCRIPT_MOVE]");
        }

        E_SCRIPT_TYPE T_ScriptType = ((C_ScriptComponent*)P_M_Script_s[_SCRIPT_MOVE])->MF_Get_ScriptType();

        if (T_ScriptType != _SCRIPT_MOVE)                                   // ����ڵ�
        {
            POPUP_DEBUG(L"T_ScriptType != _SCRIPT_MOVE", L"in C_MoveScript* MF_Get_ComponentByReturnType<C_MoveScript>(), T_ScriptType != _SCRIPT_MOVE")
        }
        return (C_MoveScript*)P_M_Script_s[_SCRIPT_MOVE];
    }

    ////// C_FSMScript Ÿ�Կ� ���� Ư��ȭ
    template <>
    C_FSMScript* MF_Get_ComponentByReturnType<C_FSMScript>()                      // C_FSMScript*
    {
        if (nullptr == P_M_Script_s[_SCRIPT_NPC])                           // ����ڵ�
        {
            POPUP_DEBUG(L"nullptr == P_M_Script_s[_SCRIPT_NPC]", L"in C_CameraScript* MF_Get_ComponentByReturnType<C_CameraScript>(), nullptr == P_M_Script_s[_SCRIPT_NPC]");
        }

        E_SCRIPT_TYPE T_ScriptType = ((C_ScriptComponent*)P_M_Script_s[_SCRIPT_NPC])->MF_Get_ScriptType();

        if (T_ScriptType != _SCRIPT_NPC)                                    // ����ڵ�
        {
            POPUP_DEBUG(L"T_ScriptType != _SCRIPT_NPC", L"in C_FSMScript* MF_Get_ComponentByReturnType<C_FSMScript>(), T_ScriptType != _SCRIPT_NPC")
        }
        return (C_FSMScript*)P_M_Script_s[_SCRIPT_NPC];
    }

    ////// C_CameraScript Ÿ�Կ� ���� Ư��ȭ
    template <>
    C_CameraScript* MF_Get_ComponentByReturnType<C_CameraScript>()                // C_CameraScript*
    {
        if (nullptr == P_M_Script_s[_SCRIPT_CAMERA])                        // ����ڵ�
        {
            POPUP_DEBUG(L"nullptr == P_M_Script_s[_SCRIPT_CAMERA]", L"in C_CameraScript* MF_Get_ComponentByReturnType<C_CameraScript>(), nullptr == P_M_Script_s[_SCRIPT_CAMERA]");
        }

        E_SCRIPT_TYPE T_ScriptType = ((C_ScriptComponent*)P_M_Script_s[_SCRIPT_CAMERA])->MF_Get_ScriptType();

        if (T_ScriptType != _SCRIPT_CAMERA)                                 // ����ڵ�
        {
            POPUP_DEBUG(L"T_ScriptType != _SCRIPT_CAMERA", L"in C_CameraScript* MF_Get_ComponentByReturnType<C_CameraScript>(), T_ScriptType != _SCRIPT_CAMERA")
        }
        return (C_CameraScript*)P_M_Script_s[_SCRIPT_CAMERA];
    }





};

