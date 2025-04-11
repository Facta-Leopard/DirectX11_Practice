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
    // 효율성을 위해 멤버들을 Heap으로 관리
    // Myself
    E_GROUP_INDEX                       M_GroupIndex;                                // E_GROUP_NUMBER; 본인이 속한 그룹을 표시
    E_OBJECT_TYPE                       M_ObjectType;                                // E_OBJECT_TYPE; 유의 개선하는 부분으로 충돌부분을 계층적 검사를 위한 것; 향후, 불변(const)하게 하는 것에 생각해보는 것이 좋겠음

    // Object
    C_Object*                           M_ParentObejct;                              // C_Object*
    vector<C_Object*>                   STL_P_M_ChildObejct;                         // vector<C_Object*>


    // Component
    C_Component*                        P_M_Component_s[_COMPONENT_END];             // C_Component*
    C_RenderComponent*                  P_M_RenderComponent;                         // C_RenderComponent*; 향후, 자료형 형식으로 해서 선택식으로 하면, 중간에 확 바뀌는 그런 효과를 줄 수 있지 않을까 고민해보자.

    C_ScriptComponent*                  P_M_Script_s[_SCRIPT_END];                   // C_Script*

public:
    CLONE(C_Object)

public:
    void MF_Prepare();                                                           // 초기화 함수; 기반료소부터 준비; C_Component -> C_ScriptComponent -> Obejct

    void MF_Tick();                                                              // Tick 구분이유; 향후, Metal의 Compute Fragement로 컨버전하는 것도 생각하고 있음

    void MF_TickAfter();                                                         // 후처리 전용 Tick

    void MF_ChildTick();                                                         // 자식오브젝트 tick() 실행; 한 계층 아래만 실행

    void MF_ComponentTick();                                                     // C_RenderComponent를 작동시키기 위한 목적(단, ScriptComponent 제외)

    void MF_ComponentTickAfter();                                                // C_RenderComponent를 작동시키기 위한 목적(단, ScriptComponent 제외)

    void MF_ScriptTick();                                                        // C_ScriptComponent만 작동 목적

    void MF_Render();                                                            // Rendering 목적; 별도의 카메라 오브젝트 및 카메라 컴포넌트 함수를 이용

public:
    inline E_GROUP_INDEX MF_Get_GroupIndex()                                     // Getter; E_GROUP_TYPE은 enum구조로 내부는 그룹 명칭이 숫자인 구조임
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

    inline C_Component* MF_Get_Component(E_COMPONENT_TYPE _COMPONENTTYPE)        // Getter; 반환값을 강제로 Down Casting 해야함; 향후, Down Casting Automaically Logic 구성예정
    {
        return P_M_Component_s[_COMPONENTTYPE];
    }

    inline C_RenderComponent* MF_Get_RenderComponent()                           // Getter; 향후 C_Component나 C_ScriptComponet 형식처럼 바꿀지 생각해 보는 것이 좋겠음
    {
        return P_M_RenderComponent;
    }

    inline C_ScriptComponent* MF_Get_ScriptComponent(E_SCRIPT_TYPE _SCRIPTTYPE)  // Getter; 반환값을 강제로 Down Casting 해야함; 향후, Down Casting Automaically Logic 구성예정
    {
        return P_M_Script_s[_SCRIPTTYPE];
    }

    // 등록관련
    //// Object 등록관련
    void MF_Attach_ObjectToParentObject(C_Object* _Object);                      // Attach; 들어오는 오브젝트를 부모오브젝트에 등록

    void MF_Detach_MyselfFromParentObject();                                     // Detach; 부모오브젝트에서 자신이 등록된 상태 해제

    void MF_Attach_ObjectToChildObject(C_Object* _Object);                       // Attach; 들어오는 오브젝트를 자식오브젝트 목록에 등록

    void MF_Detach_MyselfFromChildObject();                                      // Detach; 자식오브젝트에 등록된 본인의 부모등록 상태 해제

    void MF_Detach_DeadObjectFromChildObject();                                  // Detach; 자식오브젝트 중 죽은 자식을 제거하는 함수;

    //// Component 관련
    void MF_Attach_Component(C_Component* _Component);                           // Attach; 컴포넌트 요소 등록


    // Template Function 관련
    //// 기본 Template
    template <typename T_Template>
    T_Template* MF_Get_ComponentByReturnType()                                   // T_Template*; 기본 템플릿; 사용하지 않지만, 기본설정한 것
    {
        POPUP_DEBUG(L"Nullptr", L"in T_Template* MF_Get_ComponentByReturnType(), Nullptr")
        return nullptr;
    }

    //// C_Transform 타입에 대한 특수화
    template <>
    C_Transform* MF_Get_ComponentByReturnType<C_Transform>()                      // C_Transform*
    {
        if (nullptr == P_M_Component_s[_COMPONENT_TRANSFORM])               // 방어코드
        {
            POPUP_DEBUG(L"nullptr == P_M_Component_s[_COMPONENT_TRANSFORM]", L"in C_Transform* MF_Get_ComponentByReturnType<C_Transform>(), nullptr == P_M_Component_s[_COMPONENT_TRANSFORM]");
        }
        return (C_Transform*)P_M_Component_s[_COMPONENT_TRANSFORM];
    }

    //// C_Collider2D 타입에 대한 특수화
    template <>
    C_Collider2D* MF_Get_ComponentByReturnType<C_Collider2D>()                    // C_Collider2D*
    {
        if (nullptr == P_M_Component_s[_COMPONENT_COLLIDER_2D])             // 방어코드
        {
            POPUP_DEBUG(L"component", L"Failed");
        }
        return (C_Collider2D*)P_M_Component_s[_COMPONENT_COLLIDER_2D];
    }

    //// C_Light2D 타입에 대한 특수화
    template <>
    C_Light2D* MF_Get_ComponentByReturnType<C_Light2D>()                          // C_Light2D*
    {
        if (nullptr == P_M_Component_s[_COMPONENT_LIGHT_2D])                // 방어코드
        {
            POPUP_DEBUG(L"component", L"Failed");
        }
        return (C_Light2D*)P_M_Component_s[_COMPONENT_LIGHT_2D];
    }

    //// C_CameraComponent 타입에 대한 특수화
    template <>
    C_CameraComponent* MF_Get_ComponentByReturnType<C_CameraComponent>()          // C_CameraComponent*
    {
        if (nullptr == P_M_Component_s[_COMPONENT_CAMERA])                  // 방어코드
        {
            POPUP_DEBUG(L"component", L"Failed");
        }
        return (C_CameraComponent*)P_M_Component_s[_COMPONENT_CAMERA];
    }

    //// C_MeshRender 타입에 대한 특수화
    template <>
    C_MeshRender* MF_Get_ComponentByReturnType<C_MeshRender>()                    // C_MeshRender*
    {
        if (nullptr == P_M_Component_s[_COMPONENT_MESH_RENDER])             // 방어코드
        {
            POPUP_DEBUG(L"component", L"Failed");
        }
        return (C_MeshRender*)P_M_Component_s[_COMPONENT_MESH_RENDER];
    }

    //// C_SpriteRender 타입에 대한 특수화
    template <>
    C_SpriteRender* MF_Get_ComponentByReturnType<C_SpriteRender>()                // C_SpriteRender*
    {
        if (nullptr == P_M_Component_s[_COMPONENT_SPRITE_RENDER])           // 방어코드
        {
            POPUP_DEBUG(L"component", L"Failed");
        }
        return (C_SpriteRender*)P_M_Component_s[_COMPONENT_SPRITE_RENDER];
    }

    //// C_FlipbookRender 타입에 대한 특수화
    template <>
    C_FlipbookRender* MF_Get_ComponentByReturnType<C_FlipbookRender>()            // C_FlipbookRender*
    {
        if (nullptr == P_M_Component_s[_COMPONENT_FLIPBOOK_RENDER])         // 방어코드
        {
            POPUP_DEBUG(L"component", L"Failed");
        }
        return (C_FlipbookRender*)P_M_Component_s[_COMPONENT_FLIPBOOK_RENDER];
    }

    //// C_TileRender 타입에 대한 특수화
    template <>
    C_TileRender* MF_Get_ComponentByReturnType<C_TileRender>()                    // C_TileRender*
    {
        if (nullptr == P_M_Component_s[_COMPONENT_TILE_RENDER])             // 방어코드
        {
            POPUP_DEBUG(L"component", L"Failed");
        }
        return (C_TileRender*)P_M_Component_s[_COMPONENT_TILE_RENDER];
    }

    //// C_ParticleRender 타입에 대한 특수화
    template <>
    C_ParticleRender* MF_Get_ComponentByReturnType<C_ParticleRender>()            // C_ParticleRender*
    {
        if (nullptr == P_M_Component_s[_COMPONENT_PARTICLE_RENDER])         // 방어코드
        {
            POPUP_DEBUG(L"component", L"Failed");
        }
        return (C_ParticleRender*)P_M_Component_s[_COMPONENT_PARTICLE_RENDER];
    }

    //// C_RenderComponent 타입에 대한 특수화
    template <>
    C_RenderComponent* MF_Get_ComponentByReturnType<C_RenderComponent>()          // C_RenderComponent*
    {
        if (nullptr == P_M_RenderComponent)                                 // 방어코드
        {
            POPUP_DEBUG(L"nullptr == P_M_RenderComponent", L"in C_RenderComponent* MF_Get_ComponentByReturnType<C_RenderComponent>(), nullptr == P_M_RenderComponent");
        }
        return (C_RenderComponent*)P_M_RenderComponent;
    }

    //// C_ScriptComponent 타입에 대한 특수화
    ////// C_RigidScript 타입에 대한 특수화
    template <>
    C_RigidScript* MF_Get_ComponentByReturnType<C_RigidScript>()                  // C_RigidScript*
    {
        if (nullptr == P_M_Script_s[_SCRIPT_RIGID])                         // 방어코드
        {
            POPUP_DEBUG(L"nullptr == P_M_Script_s[_SCRIPT_RIGID]", L"in C_CameraScript* MF_Get_ComponentByReturnType<C_CameraScript>(), nullptr == P_M_Script_s[_SCRIPT_RIGID]");
        }

        E_SCRIPT_TYPE T_ScriptType = ((C_ScriptComponent*)P_M_Script_s[_SCRIPT_RIGID])->MF_Get_ScriptType();

        if (T_ScriptType != _SCRIPT_RIGID)                                  // 방어코드
        {
            POPUP_DEBUG(L"T_ScriptType != _SCRIPT_RIGID", L"in C_RigidScript* MF_Get_ComponentByReturnType<C_RigidScript>(), T_ScriptType != _SCRIPT_RIGID")
        }
        return (C_RigidScript*)P_M_Script_s[_SCRIPT_RIGID];
    }

    ////// C_StateScript 타입에 대한 특수화
    template <>
    C_StateScript* MF_Get_ComponentByReturnType<C_StateScript>()                  // C_StateScript*
    {
        if (nullptr == P_M_Script_s[_SCRIPT_STATE])                         // 방어코드
        {
            POPUP_DEBUG(L"nullptr == P_M_Script_s[_SCRIPT_STATE]", L"in C_CameraScript* MF_Get_ComponentByReturnType<C_CameraScript>(), nullptr == P_M_Script_s[_SCRIPT_STATE]");
        }

        E_SCRIPT_TYPE T_ScriptType = ((C_ScriptComponent*)P_M_Script_s[_SCRIPT_STATE])->MF_Get_ScriptType();

        if (T_ScriptType != _SCRIPT_STATE)                                  // 방어코드
        {
            POPUP_DEBUG(L"T_ScriptType != _SCRIPT_STATE", L"in C_StateScript* MF_Get_ComponentByReturnType<C_StateScript>(), T_ScriptType != _SCRIPT_STATE")
        }
        return (C_StateScript*)P_M_Script_s[_SCRIPT_STATE];
    }

    ////// C_MoveScript 타입에 대한 특수화
    template <>
    C_MoveScript* MF_Get_ComponentByReturnType<C_MoveScript>()                    // C_MoveScript*
    {
        if (nullptr == P_M_Script_s[_SCRIPT_MOVE])                          // 방어코드
        {
            POPUP_DEBUG(L"nullptr == P_M_Script_s[_SCRIPT_MOVE]", L"in C_CameraScript* MF_Get_ComponentByReturnType<C_CameraScript>(), nullptr == P_M_Script_s[_SCRIPT_MOVE]");
        }

        E_SCRIPT_TYPE T_ScriptType = ((C_ScriptComponent*)P_M_Script_s[_SCRIPT_MOVE])->MF_Get_ScriptType();

        if (T_ScriptType != _SCRIPT_MOVE)                                   // 방어코드
        {
            POPUP_DEBUG(L"T_ScriptType != _SCRIPT_MOVE", L"in C_MoveScript* MF_Get_ComponentByReturnType<C_MoveScript>(), T_ScriptType != _SCRIPT_MOVE")
        }
        return (C_MoveScript*)P_M_Script_s[_SCRIPT_MOVE];
    }

    ////// C_FSMScript 타입에 대한 특수화
    template <>
    C_FSMScript* MF_Get_ComponentByReturnType<C_FSMScript>()                      // C_FSMScript*
    {
        if (nullptr == P_M_Script_s[_SCRIPT_NPC])                           // 방어코드
        {
            POPUP_DEBUG(L"nullptr == P_M_Script_s[_SCRIPT_NPC]", L"in C_CameraScript* MF_Get_ComponentByReturnType<C_CameraScript>(), nullptr == P_M_Script_s[_SCRIPT_NPC]");
        }

        E_SCRIPT_TYPE T_ScriptType = ((C_ScriptComponent*)P_M_Script_s[_SCRIPT_NPC])->MF_Get_ScriptType();

        if (T_ScriptType != _SCRIPT_NPC)                                    // 방어코드
        {
            POPUP_DEBUG(L"T_ScriptType != _SCRIPT_NPC", L"in C_FSMScript* MF_Get_ComponentByReturnType<C_FSMScript>(), T_ScriptType != _SCRIPT_NPC")
        }
        return (C_FSMScript*)P_M_Script_s[_SCRIPT_NPC];
    }

    ////// C_CameraScript 타입에 대한 특수화
    template <>
    C_CameraScript* MF_Get_ComponentByReturnType<C_CameraScript>()                // C_CameraScript*
    {
        if (nullptr == P_M_Script_s[_SCRIPT_CAMERA])                        // 방어코드
        {
            POPUP_DEBUG(L"nullptr == P_M_Script_s[_SCRIPT_CAMERA]", L"in C_CameraScript* MF_Get_ComponentByReturnType<C_CameraScript>(), nullptr == P_M_Script_s[_SCRIPT_CAMERA]");
        }

        E_SCRIPT_TYPE T_ScriptType = ((C_ScriptComponent*)P_M_Script_s[_SCRIPT_CAMERA])->MF_Get_ScriptType();

        if (T_ScriptType != _SCRIPT_CAMERA)                                 // 방어코드
        {
            POPUP_DEBUG(L"T_ScriptType != _SCRIPT_CAMERA", L"in C_CameraScript* MF_Get_ComponentByReturnType<C_CameraScript>(), T_ScriptType != _SCRIPT_CAMERA")
        }
        return (C_CameraScript*)P_M_Script_s[_SCRIPT_CAMERA];
    }





};

