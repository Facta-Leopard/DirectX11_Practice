#include "pch.h"
#include "C_FlipBook.h"

C_FlipBook::C_FlipBook()
	: C_Resource(_RESOURCE_FLIPBOOK)

	, STL_SP_M_Sprite{}
{
}

C_FlipBook::~C_FlipBook()
{
	STL_SP_M_Sprite.clear();
}