#pragma once
#include "C_RenderComponent.h"
class C_ParticleRender :
    public C_RenderComponent
{
public:
    C_ParticleRender();

protected:
    C_ParticleRender(const C_ParticleRender& _Origin);

public:
    ~C_ParticleRender();

public:
    CLONE(C_ParticleRender)

    virtual void MF_Prepare() override;

    virtual void MF_ComponentTick() override;

    virtual void MF_ComponentTickAfter() override;

    virtual void MF_Render() override;

    virtual C_ParticleRender* MF_Get_Myself() override { return this; }
};

