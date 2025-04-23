#include "pch.h"
#include "C_Sprite.h"

C_Sprite::C_Sprite()
	: C_Resource(_RESOURCE_SPRITE)

	, SP_M_AtlasTexture{}
	, XM_VEC2_M_AtlasTextureSize{}

	, XM_VEC2_M_TopLeftPoint{}
	, XM_VEC2_M_SpriteSize{}
	, XM_VEC2_M_SpriteOffset{}
{

}

C_Sprite::~C_Sprite()
{
}
