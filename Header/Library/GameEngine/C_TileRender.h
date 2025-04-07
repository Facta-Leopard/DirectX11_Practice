#pragma once
#include "C_RenderComponent.h"
class C_TileRender :
    public C_RenderComponent
{
public:
    C_TileRender();

protected:
    C_TileRender(const C_TileRender& _Origin);

public:
    ~C_TileRender();

public:
    CLONE(C_TileRender)

    virtual void MF_ComponentTick() override;

    virtual C_TileRender* MF_GetMyself() override
    {
        return this;
    };
};

