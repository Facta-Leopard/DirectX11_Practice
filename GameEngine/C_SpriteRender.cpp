#include "pch.h"
#include "C_SpriteRender.h"

#include "C_RenderComponent.h"
#include "C_Material.h"

C_SpriteRender::C_SpriteRender()
	: C_RenderComponent(_COMPONENT_SPRITE_RENDER)

	, SP_M_Sprite{}
{

}

C_SpriteRender::C_SpriteRender(const C_SpriteRender& _Origin)
	: C_RenderComponent(_Origin)

	, SP_M_Sprite{_Origin.SP_M_Sprite}
{

}

C_SpriteRender::~C_SpriteRender()
{

}

void C_SpriteRender::MF_Prepare()
{
}

void C_SpriteRender::MF_ComponentTick()
{
}

void C_SpriteRender::MF_ComponentTickAfter()
{
}

void C_SpriteRender::MF_Render()
{
	// 위치정보 업데이트
	((C_Transform*)MF_Get_OwnerObject()->MF_Get_Component(_COMPONENT_TRANSFORM))->MF_Bind_Transform();

	// 사용할 쉐이더 바인딩	
	if (nullptr != SP_M_Sprite.get())// 향후, 에셋 구성하고 나서 구현필요
	{
	}
}
