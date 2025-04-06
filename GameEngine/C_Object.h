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
    // 효율성을 위해 멤버들을 Heap으로 관리
    // Myself
    E_GROUP_TYPE                        M_GroupType;                                // E_GROUP_NUMBER; 본인이 속한 그룹을 표시
    bool                                M_IsDead;                                   // bool; 본인이 죽었는지 여부

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
    void MF_Prepare();                                                  // 초기화 함수

    void MF_Tick();                                                     // Tick 구분이유; 향후, Metal의 Compute Fragement로 컨버전하는 것도 생각하고 있음

    void MF_ComponentTick();                                            // C_RenderComponent를 작동시키기 위한 목적(단, ScriptComponent 제외)

    void MF_ScriptTick();                                               // C_ScriptComponent만 작동 목적

    void MF_Render();                                                   // Rendering 목적; 별도의 카메라 오브젝트 및 카메라 컴포넌트 함수를 이용


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

    // Object 관련
    void MF_AttachObjectToParentObject(C_Object* _Object);              // Attach; 들어오는 오브젝트를 부모오브젝트에 등록

    void MF_DetachMyselfFromParentObject();                             // Detach; 부모오브젝트에서 자신이 등록된 상태 해제


    void MF_AttachObjectToChildObject(C_Object* _Object);               // Attach; 들어오는 오브젝트를 자식오브젝트 목록에 등록

    void MF_DetachMyselfFromChildObject();                              // Detach; 자식오브젝트에 등록된 본인의 부모등록 상태 해제

    // Component 관련
    void MF_AttachComponent(C_Component* _Component);                   // Attach; 컴포넌트 요소 등록

    // 모듈함수
    void MF_ChildTick();                                                // 자식오브젝트 tick() 실행; 한 계층 아래만 실행

};

