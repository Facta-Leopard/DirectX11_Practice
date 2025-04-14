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

    inline C_Component* MF_Get_Component(E_COMPONENT_TYPE _COMPONENTTYPE)        // Getter; 반환값을 강제로 Down Casting 해야함; 향후, Down Casting Automaically Logic 구성예정
    {
        return P_M_Component_s[_COMPONENTTYPE];
    }

    inline C_Transform* MF_Get_TransformComponent()
    {
        if (nullptr == P_M_Component_s[_COMPONENT_TRANSFORM])           // 조기반환
        {
            POPUP_DEBUG(L"nullptr == P_M_Component_s[_COMPONENT_TRANSFORM]", L"in C_Transform* MF_Get_TransformComponent(), nullptr == P_M_Component_s[_COMPONENT_TRANSFORM]")
            return nullptr;
        }
        return (C_Transform*)P_M_Component_s[_COMPONENT_TRANSFORM];
    }

    inline C_Collider2D* MF_Get_Collider2DComponent()
    {
        if (nullptr == P_M_Component_s[_COMPONENT_COLLIDER2D])           // 조기반환
        {
            POPUP_DEBUG(L"nullptr == P_M_Component_s[_COMPONENT_COLLIDER2D]", L"in C_Transform* MF_Get_Collider2DComponent(), nullptr == P_M_Component_s[_COMPONENT_COLLIDER2D]")
                return nullptr;
        }
        return (C_Collider2D*)P_M_Component_s[_COMPONENT_COLLIDER2D];
    }

    inline C_StateComponent* MF_Get_StateComponent()
    {
        if (nullptr == P_M_Component_s[_COMPONENT_STATE])           // 조기반환
        {
            POPUP_DEBUG(L"nullptr == P_M_Component_s[_COMPONENT_STATE]", L"in C_Transform* MF_Get_StateComponent(), nullptr == P_M_Component_s[_COMPONENT_STATE]")
                return nullptr;
        }
        return (C_StateComponent*)P_M_Component_s[_COMPONENT_STATE];
    }

    inline C_Light2D* MF_Get_Light2DComponent()
    {
        if (nullptr == P_M_Component_s[_COMPONENT_LIGHT2D])           // 조기반환
        {
            POPUP_DEBUG(L"nullptr == P_M_Component_s[_COMPONENT_LIGHT2D]", L"in C_Transform* MF_Get_Light2DComponent(), nullptr == P_M_Component_s[_COMPONENT_LIGHT2D]")
                return nullptr;
        }
        return (C_Light2D*)P_M_Component_s[_COMPONENT_LIGHT2D];
    }

    inline C_CameraComponent* MF_Get_CameraComponent()
    {
        if (nullptr == P_M_Component_s[_COMPONENT_CAMERA])           // 조기반환
        {
            POPUP_DEBUG(L"nullptr == P_M_Component_s[_COMPONENT_CAMERA]", L"in C_Transform* MF_Get_CameraComponent(), nullptr == P_M_Component_s[_COMPONENT_CAMERA]")
                return nullptr;
        }
        return (C_CameraComponent*)P_M_Component_s[_COMPONENT_CAMERA];
    }

    inline C_RenderComponent* MF_Get_RenderComponent()                           // Getter; 향후 C_Component나 C_ScriptComponet 형식처럼 바꿀지 생각해 보는 것이 좋겠음
    {
        if (nullptr == P_M_RenderComponent)           // 조기반환
        {
            POPUP_DEBUG(L"nullptr == P_M_RenderComponent", L"in C_Transform* MF_Get_RenderComponent(), nullptr == P_M_RenderComponent")
                return nullptr;
        }
        return P_M_RenderComponent;
    }

    // 향후, 리소스 관련 작성시 렌더 컴포넌트 게터 확장

    inline C_ScriptComponent* MF_Get_ScriptComponent(E_SCRIPT_TYPE _SCRIPTTYPE)  // Getter; 반환값을 강제로 Down Casting 해야함; 향후, Down Casting Automaically Logic 구성예정
    {
        if (nullptr == P_M_Script_s[_SCRIPTTYPE])           // 조기반환
        {
            POPUP_DEBUG(L"nullptr == P_M_Script_s[_SCRIPTTYPE]", L"in C_Transform* MF_Get_ScriptComponent(), nullptr == P_M_Script_s[_SCRIPTTYPE]")
                return nullptr;
        }
        return P_M_Script_s[_SCRIPTTYPE];
    }

    // 향후, 스크립트 관련 작성시 렌더 컴포넌트 게터 확장

    // 등록관련
    //// Object 등록관련
    void MF_Attach_ObjectToParentObject(C_Object* _Object);                      // Attach; 들어오는 오브젝트를 부모오브젝트에 등록

    void MF_Detach_MyselfFromParentObject();                                     // Detach; 부모오브젝트에서 자신이 등록된 상태 해제

    void MF_Attach_ObjectToChildObject(C_Object* _Object);                       // Attach; 들어오는 오브젝트를 자식오브젝트 목록에 등록

    void MF_Detach_MyselfFromChildObject();                                      // Detach; 자식오브젝트에 등록된 본인의 부모등록 상태 해제

    void MF_Detach_DeadObjectFromChildObject();                                  // Detach; 자식오브젝트 중 죽은 자식을 제거하는 함수;

    //// Component 관련
    void MF_Attach_Component(C_Component* _Component);                           // Attach; 컴포넌트 요소 등록

    void MF_Detach_Component(C_Component* _Component);                           // Detach; 컴포넌트 요소 해제




};