#include "pch.h"
#include "C_Sprite.h"

C_Sprite::C_Sprite()
	: C_Resource(_RESOURCE_SPRITE)

	, SP_M_AtlasTexture{}
	, VEC2_M_AtlasTextureSize{}

	, VEC2_M_TopLeftPoint{}
	, VEC2_M_SpriteSize{}
	, VEC2_M_SpriteOffset{}
{

}

C_Sprite::~C_Sprite()
{
}
