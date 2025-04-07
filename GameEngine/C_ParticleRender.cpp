#include "pch.h"
#include "C_ParticleRender.h"

C_ParticleRender::C_ParticleRender()
	: C_RenderComponent(_COMPONENT_PARTICLE_RENDER)
{
}

C_ParticleRender::C_ParticleRender(const C_ParticleRender& _Origin)
	: C_RenderComponent(_Origin)
{
}

C_ParticleRender::~C_ParticleRender()
{
}

void C_ParticleRender::MF_Prepare()
{
}

void C_ParticleRender::MF_ComponentTick()
{
}

void C_ParticleRender::MF_Render()
{
}
