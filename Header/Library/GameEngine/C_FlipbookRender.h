#pragma once
#include "C_RenderComponent.h"
class C_FlipBookRender :
    public C_RenderComponent
{
public:
    C_FlipBookRender();

protected:
    C_FlipBookRender(const C_FlipBookRender& _Origin);

public:
    ~C_FlipBookRender();

public:
    CLONE(C_FlipBookRender)

    virtual void MF_Prepare() override;

    virtual void MF_ComponentTick() override;

    virtual void MF_ComponentTickAfter() override;

    virtual void MF_Render() override;
};

