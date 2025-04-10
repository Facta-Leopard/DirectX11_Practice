#pragma once
#include "C_RenderComponent.h"
class C_SpriteRender :
    public C_RenderComponent
{
public:
    C_SpriteRender();

protected:
    C_SpriteRender(const C_SpriteRender& _Origin);

public:
    ~C_SpriteRender();

public:
    CLONE(C_SpriteRender)

    virtual void MF_Prepare() override;

    virtual void MF_ComponentTick() override;

    virtual void MF_ComponentTickAfter() override;

    virtual void MF_Render() override;

};

