#pragma once

#include "define.h"

#include "C_Entity.h"
#include "component.h"

class C_Object :
    public C_Entity
{
    friend class C_Group;

public:
    C_Object();

protected:
    C_Object(const C_Object& _Origin);
    
public:
    ~C_Object();

protected:
    // ȿ������ ���� ������� Heap���� ����
    // Myself
    E_GROUP_TYPE                        M_GroupIndex;                                // E_GROUP_NUMBER; ������ ���� �׷��� ǥ��
    bool                                M_IsLive;                                    // bool; ������ �׾����� ����

    // Object
    C_Object*                           M_ParentObejct;                              // C_Object*
    vector<C_Object*>                   STL_P_M_ChildObejct;                         // vector<C_Object*>


    // Component
    C_Component*                        P_M_Component_s[_COMPONENT_END];             // C_Component*
    C_RenderComponent*                  P_M_RenderComponent;                         // C_RenderComponent*

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
    inline E_GROUP_TYPE MF_Get_GroupType()                                       // Getter
    {
        return M_GroupIndex;
    }

    inline void MF_Set_GroupIndex(E_GROUP_TYPE _M_GroupIndex)                    // Setter
    {
        M_GroupIndex = _M_GroupIndex;
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

    // Template ����
    template<typename Template>
    Template* MF_Get_ReturnTypeBy(E_COMPONENT_TYPE _ComponentType)                      // Template; ����! C++ 17�� if constexpr�� ���ؼ� ������ ��! C++ 17 �̻󿡼��� ��밡��!;
    {
        switch (_ComponentType)
        {
        case _COMPONENT_TRANSFORM:
            if constexpr (C_Transform == Template)
                return (Template*)P_M_Component_s[_COMPONENT_TRANSFORM];
            break;
        case _COMPONENT_COLLIDER_2D:
            else if constexpr (C_Collider2D == Template)
                return (Template*)P_M_Component_s[_COMPONENT_COLLIDER_2D];
            break;
        case _COMPONENT_LIGHT_2D:
            else if constexpr (C_Light2D == Template)
                return (Template*)P_M_Component_s[_COMPONENT_LIGHT_2D];
            break;
        case _COMPONENT_CAMERA:
            else if constexpr (C_CameraComponent == Template)
                return (Template*)P_M_Component_s[_COMPONENT_CAMERA];
            break;
        case _COMPONENT_MESH_RENDER:
            else if constexpr (C_MeshRender == Template)
                return (Template*)P_M_Component_s[_COMPONENT_MESH_RENDER];
            break;
        case _COMPONENT_SPRITE_RENDER:
            else if constexpr (C_SpriteRender == Template)
                return (Template*)P_M_Component_s[_COMPONENT_SPRITE_RENDER];
            break;
        case _COMPONENT_FLIPBOOK_RENDER:
            else if constexpr (C_FlipbookRender == Template)
                return (Template*)P_M_Component_s[_COMPONENT_FLIPBOOK_RENDER];
            break;
        case _COMPONENT_TILE_RENDER:
            else if constexpr (C_TileRender == Template)
                return (Template*)P_M_Component_s[_COMPONENT_TILE_RENDER];
            break;
        case _COMPONENT_PARTICLE_RENDER:
            else if constexpr (C_ParticleRender == Template)
                return (Template*)P_M_Component_s[_COMPONENT_PARTICLE_RENDER];
            break;
        case _COMPONENT_SCRIPT:
            if constexpr (C_ScriptComponent == Template)               // ����! ScriptComponent�� �߰��� ����ÿ�, �� ���� �ٽ� ����غ�����
            {
                E_SCRIPT_TYPE T_ScriptType = (C_ScriptComponent*)Template1->MF_GetScriptType();
                switch (T_ScriptType)
                {
                case _SCRIPT_RIGID:
                    if constexpr (C_RigidScript == Template)
                        return (Template*)P_M_Component_s[_COMPONENT_SCRIPT];
                    break;
                case _SCRIPT_STATE:
                    if constexpr (C_StateScript == Template)
                        return (Template*)P_M_Component_s[_COMPONENT_SCRIPT];
                    break;
                case _SCRIPT_MOVE:
                    if constexpr (C_MoveScript == Template)
                        return (Template*)P_M_Component_s[_COMPONENT_SCRIPT];
                    break;
                case _SCRIPT_NPC:
                    if constexpr (C_NPCScript == Template)
                        return (Template*)P_M_Component_s[_COMPONENT_SCRIPT];
                    break;
                case _SCRIPT_CAMERA:
                    if constexpr (C_CameraScript == Template)
                        return (Template*)P_M_Component_s[_COMPONENT_SCRIPT];
                    break;
                case _SCRIPT_END:
                default:
                    POPUP(L"C_ScriptComponent == Template", L"in Template1* MF_Get_ReturnTypeBy(E_COMPONENT_TYPE _ComponentType) on C_Object, C_ScriptComponent == Template Needed ReCoding")
                        return nullptr;
                }
            }
            break;
        case _COMPONENT_RENDER:
        case _COMPONENT_END:
        default:
            break;
        }



















        else
        {
            POPUP_DEBUG(L"Component Type Is Mismatch ", L"in T* MF_Get_ReturnTypeBy(E_COMPONENT_TYPE _ComponentType) on C_Object Class, Component Type Is Mismatch")
            assert(true)
            return nullptr;
        }
    }

};

