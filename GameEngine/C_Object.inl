#pragma once

#include "C_Object.h"

// ����ȭ �ʿ�� ������ ��

// Template Function ����
//// �⺻ Template
template <typename T_Template>
inline T_Template* C_Object::MF_Get_ComponentByReturnType()                                   // T_Template*; �⺻ ���ø�; ������� ������, �⺻������ ��
{
    POPUP_DEBUG(L"Nullptr", L"in T_Template* MF_Get_ComponentByReturnType(), Nullptr")
        return nullptr;
}

//// C_Transform Ÿ�Կ� ���� Ư��ȭ
template <>
inline C_Transform* C_Object::MF_Get_ComponentByReturnType<C_Transform>()                      // C_Transform*
{
    if (nullptr == P_M_Component_s[_COMPONENT_TRANSFORM])               // ����ڵ�
    {
        POPUP_DEBUG(L"nullptr == P_M_Component_s[_COMPONENT_TRANSFORM]", L"in C_Transform* MF_Get_ComponentByReturnType<C_Transform>(), nullptr == P_M_Component_s[_COMPONENT_TRANSFORM]");
    }
    return (C_Transform*)P_M_Component_s[_COMPONENT_TRANSFORM];
}

//// C_Collider2D Ÿ�Կ� ���� Ư��ȭ
template <>
inline C_Collider2D* C_Object::MF_Get_ComponentByReturnType<C_Collider2D>()                    // C_Collider2D*
{
    if (nullptr == P_M_Component_s[_COMPONENT_COLLIDER_2D])             // ����ڵ�
    {
        POPUP_DEBUG(L"nullptr == P_M_Component_s[_COMPONENT_COLLIDER_2D]", L"in C_Collider2D* MF_Get_ComponentByReturnType<C_Collider2D>(), nullptr == P_M_Component_s[_COMPONENT_COLLIDER_2D]");
    }
    return (C_Collider2D*)P_M_Component_s[_COMPONENT_COLLIDER_2D];
}

//// C_StateComponent Ÿ�Կ� ���� Ư��ȭ
template <>
inline C_StateComponent* C_Object::MF_Get_ComponentByReturnType<C_StateComponent>()            // C_StateScript*
{
    if (nullptr == P_M_Component_s[_COMPONENT_STATE])                   // ����ڵ�
    {
        POPUP_DEBUG(L"nullptr == P_M_Component_s[_COMPONENT_STATE]", L"in C_StateComponent* MF_Get_ComponentByReturnType<C_StateComponent>(), nullptr == P_M_Component_s[_COMPONENT_STATE]");
    }
    return (C_StateComponent*)P_M_Component_s[_COMPONENT_STATE];
}

//// C_Light2D Ÿ�Կ� ���� Ư��ȭ
template <>
inline C_Light2D* C_Object::MF_Get_ComponentByReturnType<C_Light2D>()                          // C_Light2D*
{
    if (nullptr == P_M_Component_s[_COMPONENT_LIGHT_2D])                // ����ڵ�
    {
        POPUP_DEBUG(L"nullptr == P_M_Component_s[_COMPONENT_LIGHT_2D]", L"in C_Light2D* MF_Get_ComponentByReturnType<C_Light2D>(), nullptr == P_M_Component_s[_COMPONENT_LIGHT_2D]");
    }
    return (C_Light2D*)P_M_Component_s[_COMPONENT_LIGHT_2D];
}

//// C_CameraComponent Ÿ�Կ� ���� Ư��ȭ
template <>
inline C_CameraComponent* C_Object::MF_Get_ComponentByReturnType<C_CameraComponent>()          // C_CameraComponent*
{
    if (nullptr == P_M_Component_s[_COMPONENT_CAMERA])                  // ����ڵ�
    {
        POPUP_DEBUG(L"nullptr == P_M_Component_s[_COMPONENT_CAMERA]", L"in C_CameraComponent* MF_Get_ComponentByReturnType<C_CameraComponent>(), nullptr == P_M_Component_s[_COMPONENT_CAMERA]");
    }
    return (C_CameraComponent*)P_M_Component_s[_COMPONENT_CAMERA];
}

//// C_MeshRender Ÿ�Կ� ���� Ư��ȭ
template <>
inline C_MeshRender* C_Object::MF_Get_ComponentByReturnType<C_MeshRender>()                    // C_MeshRender*
{
    if (nullptr == P_M_Component_s[_COMPONENT_MESH_RENDER])             // ����ڵ�
    {
        POPUP_DEBUG(L"nullptr == P_M_Component_s[_COMPONENT_MESH_RENDER]", L"in C_MeshRender* MF_Get_ComponentByReturnType<C_MeshRender>(), nullptr == P_M_Component_s[_COMPONENT_MESH_RENDER]");
    }
    return (C_MeshRender*)P_M_Component_s[_COMPONENT_MESH_RENDER];
}

//// C_SpriteRender Ÿ�Կ� ���� Ư��ȭ
template <>
inline C_SpriteRender* C_Object::MF_Get_ComponentByReturnType<C_SpriteRender>()                // C_SpriteRender*
{
    if (nullptr == P_M_Component_s[_COMPONENT_SPRITE_RENDER])           // ����ڵ�
    {
        POPUP_DEBUG(L"nullptr == P_M_Component_s[_COMPONENT_SPRITE_RENDER]", L"in C_SpriteRender* MF_Get_ComponentByReturnType<C_SpriteRender>(), nullptr == P_M_Component_s[_COMPONENT_SPRITE_RENDER]");
    }
    return (C_SpriteRender*)P_M_Component_s[_COMPONENT_SPRITE_RENDER];
}

//// C_FlipbookRender Ÿ�Կ� ���� Ư��ȭ
template <>
inline C_FlipbookRender* C_Object::MF_Get_ComponentByReturnType<C_FlipbookRender>()            // C_FlipbookRender*
{
    if (nullptr == P_M_Component_s[_COMPONENT_FLIPBOOK_RENDER])         // ����ڵ�
    {
        POPUP_DEBUG(L"nullptr == P_M_Component_s[_COMPONENT_FLIPBOOK_RENDER]", L"in C_FlipbookRender* MF_Get_ComponentByReturnType<C_FlipbookRender>(), nullptr == P_M_Component_s[_COMPONENT_FLIPBOOK_RENDER]");
    }
    return (C_FlipbookRender*)P_M_Component_s[_COMPONENT_FLIPBOOK_RENDER];
}

//// C_TileRender Ÿ�Կ� ���� Ư��ȭ
template <>
inline C_TileRender* C_Object::MF_Get_ComponentByReturnType<C_TileRender>()                    // C_TileRender*
{
    if (nullptr == P_M_Component_s[_COMPONENT_TILE_RENDER])             // ����ڵ�
    {
        POPUP_DEBUG(L"nullptr == P_M_Component_s[_COMPONENT_TILE_RENDER]", L"in C_TileRender* MF_Get_ComponentByReturnType<C_TileRender>(), nullptr == P_M_Component_s[_COMPONENT_TILE_RENDER]");
    }
    return (C_TileRender*)P_M_Component_s[_COMPONENT_TILE_RENDER];
}

//// C_ParticleRender Ÿ�Կ� ���� Ư��ȭ
template <>
inline C_ParticleRender* C_Object::MF_Get_ComponentByReturnType<C_ParticleRender>()            // C_ParticleRender*
{
    if (nullptr == P_M_Component_s[_COMPONENT_PARTICLE_RENDER])         // ����ڵ�
    {
        POPUP_DEBUG(L"nullptr == P_M_Component_s[_COMPONENT_PARTICLE_RENDER]", L"in C_ParticleRender* MF_Get_ComponentByReturnType<C_ParticleRender>(), nullptr == P_M_Component_s[_COMPONENT_PARTICLE_RENDER]");
    }
    return (C_ParticleRender*)P_M_Component_s[_COMPONENT_PARTICLE_RENDER];
}

//// C_RenderComponent Ÿ�Կ� ���� Ư��ȭ
template <>
inline C_RenderComponent* C_Object::MF_Get_ComponentByReturnType<C_RenderComponent>()          // C_RenderComponent*
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
inline C_RigidScript* C_Object::MF_Get_ComponentByReturnType<C_RigidScript>()                  // C_RigidScript*
{
    E_SCRIPT_TYPE T_ScriptType = P_M_Script_s[_SCRIPT_RIGID]->MF_Get_ScriptType();

    if (_SCRIPT_RIGID != T_ScriptType)                                  // ����ڵ�
    {
        POPUP_DEBUG(L"_SCRIPT_RIGID != T_ScriptType", L"in C_RigidScript* MF_Get_ComponentByReturnType<C_RigidScript>(), _SCRIPT_RIGID != T_ScriptType")
    }
    return (C_RigidScript*)P_M_Script_s[_SCRIPT_RIGID];
}

////// C_MoveScript Ÿ�Կ� ���� Ư��ȭ
template <>
inline C_MoveScript* C_Object::MF_Get_ComponentByReturnType<C_MoveScript>()                    // C_MoveScript*
{
    E_SCRIPT_TYPE T_ScriptType = P_M_Script_s[_SCRIPT_MOVE]->MF_Get_ScriptType();

    if (_SCRIPT_MOVE != T_ScriptType)                                   // ����ڵ�
    {
        POPUP_DEBUG(L"_SCRIPT_MOVE != T_ScriptType", L"in C_MoveScript* MF_Get_ComponentByReturnType<C_MoveScript>(), _SCRIPT_MOVE != T_ScriptType")
    }
    return (C_MoveScript*)P_M_Script_s[_SCRIPT_MOVE];
}

////// C_FSMScript Ÿ�Կ� ���� Ư��ȭ
template <>
inline C_FSMScript* C_Object::MF_Get_ComponentByReturnType<C_FSMScript>()                      // C_FSMScript*
{
    E_SCRIPT_TYPE T_ScriptType = P_M_Script_s[_SCRIPT_NPC]->MF_Get_ScriptType();

    if (_SCRIPT_NPC != T_ScriptType)                                    // ����ڵ�
    {
        POPUP_DEBUG(L"_SCRIPT_NPC != T_ScriptType", L"in C_FSMScript* MF_Get_ComponentByReturnType<C_FSMScript>(), _SCRIPT_NPC != T_ScriptType")
    }
    return (C_FSMScript*)P_M_Script_s[_SCRIPT_NPC];
}

////// C_CameraScript Ÿ�Կ� ���� Ư��ȭ
template <>
inline C_CameraScript* C_Object::MF_Get_ComponentByReturnType<C_CameraScript>()                // C_CameraScript*
{
    E_SCRIPT_TYPE T_ScriptType = P_M_Script_s[_SCRIPT_CAMERA]->MF_Get_ScriptType();

    if (_SCRIPT_CAMERA != T_ScriptType)                                 // ����ڵ�
    {
        POPUP_DEBUG(L"_SCRIPT_CAMERA != T_ScriptType", L"in C_CameraScript* MF_Get_ComponentByReturnType<C_CameraScript>(), _SCRIPT_CAMERA != T_ScriptType")
    }
    return (C_CameraScript*)P_M_Script_s[_SCRIPT_CAMERA];
}