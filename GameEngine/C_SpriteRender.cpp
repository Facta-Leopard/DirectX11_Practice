#include "pch.h"
#include "C_SpriteRender.h"

C_SpriteRender::C_SpriteRender()
	: C_RenderComponent(_COMPONENT_SPRITE_RENDER)
{

}

C_SpriteRender::C_SpriteRender(const C_SpriteRender& _Origin)
	: C_RenderComponent(_Origin)
{

}

C_SpriteRender::~C_SpriteRender()
{

}

void C_SpriteRender::MF_ComponentTick()
{
}
