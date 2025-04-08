#pragma once
#include "C_RenderComponent.h"
class C_FlipbookRender :
    public C_RenderComponent
{
public:
    C_FlipbookRender();

protected:
    C_FlipbookRender(const C_FlipbookRender& _Origin);

public:
    ~C_FlipbookRender();

public:
    CLONE(C_FlipbookRender)

    virtual void MF_Prepare() override;

    virtual void MF_ComponentTick() override;

    virtual void MF_ComponentTickAfter() override;

    virtual void MF_Render() override;

    virtual C_FlipbookRender* MF_Get_Myself() override
    {
        return this;
    };
};

