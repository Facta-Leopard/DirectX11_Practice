#pragma once
#include "C_RenderComponent.h"

class C_MeshRender :
    public C_RenderComponent
{
protected:
    C_MeshRender();

public:
    C_MeshRender(const C_MeshRender& _Origin);

protected:
    ~C_MeshRender();

public:
    CLONE(C_MeshRender)

    virtual void MF_ComponentTick() override;

    virtual C_MeshRender* MF_GetMyself() override
    {
        return this;
    };
};

