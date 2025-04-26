#pragma once
#include "C_RenderComponent.h"

class C_Sprite;

class C_SpriteRender :
    public C_RenderComponent
{
public:
    C_SpriteRender();

protected:
    C_SpriteRender(const C_SpriteRender& _Origin);

public:
    ~C_SpriteRender();

protected:
    shared_ptr<C_Sprite>               SP_M_Sprite;               // shared_ptr<C_Sprite>

public:
    CLONE(C_SpriteRender)

    virtual void MF_Prepare() override;

    virtual void MF_ComponentTick() override;

    virtual void MF_ComponentTickAfter() override;

    virtual void MF_Render() override;

public:
    inline shared_ptr<C_Sprite> MF_Get_Sprite()
    {
        return SP_M_Sprite;
    }

public:
    void MF_Create_MaterialOfSprite();                            // 향후, 에셋 구성하고 나서 구현필요
};

