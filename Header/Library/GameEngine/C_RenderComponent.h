#pragma once
#include "C_Component.h"

class C_Mesh;
class C_Material;

class C_RenderComponent :
    public C_Component
{
public:
    C_RenderComponent(E_COMPONENT_TYPE _E_COMPONENT);

protected:
    C_RenderComponent(const C_RenderComponent& _Origin);

public:
    ~C_RenderComponent();

protected:
    shared_ptr<C_Mesh>              SP_M_Mesh;                      // shared_ptr<C_Mesh>

    shared_ptr<C_Material>          SP_M_CommonMaterial;            // shared_ptr<C_Material>; 모든 객체가 공유하는 재질

    shared_ptr<C_Material>          SP_M_CurrentMaterial;           // shared_ptr<C_Material>; 현재 사용중인 재질
    shared_ptr<C_Material>          SP_M_CustomMaterial;            // shared_ptr<C_Material>; 커스텀해서 쓰는 재질

public:
    virtual C_RenderComponent* MF_Clone() = 0;              // Clone Function; Vertual

    virtual void MF_ComponentTick() = 0;                    // ComponentTick; Virtual

    virtual void MF_Render() = 0;                           // Render; Virtual

public:
    inline shared_ptr<C_Mesh> MF_Get_Mesh()
    {
        return SP_M_Mesh;
    }

    inline shared_ptr<C_Material> MF_Get_CommonMaterial()
    {
        return SP_M_CommonMaterial;
    }

    inline shared_ptr<C_Material> MF_Get_CurrentMaterial()
    {
        return SP_M_CurrentMaterial;
    }

    shared_ptr<C_Material> MF_Get_CustomMaterial();                             // 유의! 평소에 CustomMaterial은 비어 있다가 달라고 할 때, 만드는 것임!

public:
    inline void MF_Set_Material(shared_ptr<C_Material> _SP_Material)
    {
        SP_M_CurrentMaterial = SP_M_CommonMaterial = _SP_Material;
    }

    inline void MF_Set_Mesh(shared_ptr<C_Mesh> _SP_Mesh)
    {
        SP_M_Mesh = _SP_Mesh;
    }
};