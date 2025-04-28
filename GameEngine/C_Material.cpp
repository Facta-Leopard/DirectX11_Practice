#include "pch.h"
#include "C_Material.h"
#include "C_ConstantBuffer.h"

C_Material::C_Material()
	: C_Resource(_RESOURCE_MATERIAL)

	, SP_M_GraphicShader{}
	, DS_M_MaterialConstant{}

{
}

C_ConstantBuffer* C_Material::S_P_ConstantBuffer = nullptr;

C_Material::~C_Material()
{
}

void C_Material::MF_Bind_Material()
{
	SP_M_GraphicShader->MF_Bind_GraphicShader();

	for (int i = 0; i < (int)_TEXTURE_END; ++i)
	{
		if (nullptr != SP_M_Texture_s[i].get())
		{
			SP_M_Texture_s[(int)i]->MF_Bind_ShaderResourceViewToAllShadersBytRegister((int)i);

			// 해당 텍스처를 사용한다는 의미로 true 값 선입
			// 유의! DS_MaterialConstant 구조체의 데이터 정렬 때문에 bool아닌 SDK인 BOOL을 썻다는 점을 잊지 말 것!
			DS_M_MaterialConstant.SDK_XM_BOOL_Texture_s[(E_TEXTURE_NUMBER)i] = true;
		}
		else
		{
			ID3D11ShaderResourceView* P_T_ShaderResourceView = nullptr;
			C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->VSSetShaderResources(i, 1, &P_T_ShaderResourceView);
			C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->HSSetShaderResources(i, 1, &P_T_ShaderResourceView);
			C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->DSSetShaderResources(i, 1, &P_T_ShaderResourceView);
			C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->GSSetShaderResources(i, 1, &P_T_ShaderResourceView);
			C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->PSSetShaderResources(i, 1, &P_T_ShaderResourceView);

			// 해당 텍스처를 사용하지 않는다는 의미로 false 값 선입
			// 유의! DS_MaterialConstant 구조체의 데이터 정렬 때문에 bool아닌 SDK인 BOOL을 썻다는 점을 잊지 말 것!
			DS_M_MaterialConstant.SDK_XM_BOOL_Texture_s[(E_TEXTURE_NUMBER)i] = false;
		}
	}

	// 재질 상수값을 상수버퍼에 전달 및 바인딩
	S_P_ConstantBuffer = C_Device::SF_Get_Instance()->MF_Get_ConstantBuffer(_CONSTANTBUFFER_MATERIAL);
	S_P_ConstantBuffer->MF_Set_ConstantBufferByData(&DS_M_MaterialConstant, sizeof(DS_MaterialConstant));
	S_P_ConstantBuffer->MF_Bind_ConstantBuffer();
}
