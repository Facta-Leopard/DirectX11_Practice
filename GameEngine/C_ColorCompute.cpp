#include "pch.h"
#include "C_ColorCompute.h"

C_ColorCompute::C_ColorCompute()
{
}

C_ColorCompute::~C_ColorCompute()
{
}

void C_ColorCompute::MF_Bind_ColorCompute()
{
	if (nullptr == SP_M_Texture)		// 조기반환; 방어코드
	{
		POPUP_DEBUG(L"nullptr == SP_M_Texture", L"in C_ColorCompute::MF_Bind_ColorCompute(), nullptr == SP_M_Texture")
		return;
	}
		
	SP_M_Texture->MF_Bind_UnorderedAccessViewToComputeShadersByuRegister(0);

	DS_M_MaterialConstant.SDK_XM_FLOAT4_Constant_s[0] = VEC4_M_Color;
	DS_M_MaterialConstant.SDK_XM_UINT_Constant_s[0] = (int)SP_M_Texture->MF_Get_TextureWidth();
	DS_M_MaterialConstant.SDK_XM_UINT_Constant_s[1] = (int)SP_M_Texture->MF_Get_TextureHeight();
}

void C_ColorCompute::MF_UnBind_ColorCompute()
{
}

void C_ColorCompute::MF_Calculate_GroupXYZ()
{
	SDK_M_GroupCountX = (SP_M_Texture->MF_Get_TextureWidth()) / SDK_M_ThreadPerGroupX;		// 유의! 나누기 후 1 미만의 값은 0으로 자동 변환됨!
	SDK_M_GroupCountY = (SP_M_Texture->MF_Get_TextureHeight()) / SDK_M_ThreadPerGroupY;
	SDK_M_GroupCountZ = 1 / SDK_M_ThreadPerGroupZ;												// 향후, 이 값은 3D 배우고 나서 생각을 해보도록 하자

	if ((SP_M_Texture->MF_Get_TextureWidth()) % SDK_M_ThreadPerGroupX)
	{
		SDK_M_GroupCountX += 1;
	}
		
	if ((SP_M_Texture->MF_Get_TextureHeight()) % SDK_M_ThreadPerGroupY)
	{
		SDK_M_GroupCountY += 1;
	}

	if (0 == SDK_M_ThreadPerGroupZ)
	{
		SDK_M_GroupCountY += 1;
	}
}
