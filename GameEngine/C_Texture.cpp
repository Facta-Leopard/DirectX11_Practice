#include "pch.h"

#include "C_Texture.h"

C_Texture::C_Texture(E_RESOURCE_TYPE _RESOURCETYPE)
	: C_Resource(_RESOURCETYPE)
	, M_Scratch_Image{}

	, CP_M_D_Texture2D(nullptr)
	, M_D_TextureDesc{}
	
	, CP_M_D_RenderTagetView(nullptr)
	, CP_M_D_DepthStencilView(nullptr)
	
	, CP_M_D_ShaderResourceView(nullptr)
	, M_tRegisterNumber(-1)
	
	, CP_M_D_UnorderedAccessView{}
	, M_uRegisterNumber(-1)
{
}

C_Texture::~C_Texture()
{
}

void C_Texture::MF_Bind_ShaderResourceViewToAllShadersBytRegister(int _RegisterNumber)								// Graphic Pipeline의 모든 Shader들에 ShaderResource View 연결
{
	// Pipeline : Vertex Shader(VS) -> Hull Shader(HS, Default) -> Domain Shader(DS, Default) -> Geometry Shader(GS, Default) -> Pixel Shader(PS)
	// Vertex Shader(VS) : 정점 계산 및 UV좌표로 전달, Hull Shader(HS) : 곡률 및 밀도 계산(Tessellator와 연관), Domain Shader(DS) : UV좌표 보간, Geometry Shader(GS) : 정점 및 도형 재생성, Pixel Shader(PS) : 픽셀 계산(보통은 색깔이지만, Texel 개념으로 계산용으로 사용 가능)
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->VSSetShaderResources(_RegisterNumber, 1, CP_M_D_ShaderResourceView.GetAddressOf());		// Vertex Shader에 쉐이더리소스 뷰 연결;
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->HSSetShaderResources(_RegisterNumber, 1, CP_M_D_ShaderResourceView.GetAddressOf());		// Hull Shader에 쉐이더리소스 뷰 연결;
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->DSSetShaderResources(_RegisterNumber, 1, CP_M_D_ShaderResourceView.GetAddressOf());		// Domain Shader에 쉐이더리소스 뷰 연결;
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->GSSetShaderResources(_RegisterNumber, 1, CP_M_D_ShaderResourceView.GetAddressOf());		// Vertex Shader에 쉐이더리소스 뷰 연결;
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->PSSetShaderResources(_RegisterNumber, 1, CP_M_D_ShaderResourceView.GetAddressOf());		// Vertex Shader에 쉐이더리소스 뷰 연결;
}

void C_Texture::MF_Bind_ShaderResourceViewToComputeShadersByuRegister(int _RegisterNumber)
{
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->CSSetShaderResources(_RegisterNumber, 1, CP_M_D_ShaderResourceView.GetAddressOf());		// Domain Shader에 쉐이더리소스 뷰 연결;
	M_tRegisterNumber = _RegisterNumber;
}

void C_Texture::MF_Bind_UnorderedAccessViewToComputeShadersByuRegister(int _RegisterNumber)
{
	UINT P_T_InitialCount = -1;				// 유의! 오버플로우로 최대값으로 초기 배열값을 최대로 주기 위한 트릭!; COM객체이므로, 이런 방식을 무조건 써야함!
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->CSSetUnorderedAccessViews(_RegisterNumber, 1, CP_M_D_UnorderedAccessView.GetAddressOf(), &P_T_InitialCount);	// Domain Shader에 쉐이더리소스 뷰 연결;
	M_uRegisterNumber = _RegisterNumber;
}

void C_Texture::MF_Unbind_ShaderResourceViewFromComputeBytRegister(int _RegisterNumber)								// 유의! 함수 내 노이즈 텐스처 사용을 위한 분기를 사용!
{

	if (-1 == _RegisterNumber)
	{
		ID3D11ShaderResourceView* T_ShaderResourceView = nullptr;													// 유의! Component Object Model(COM)형식이므로, 뷰를 이중포인터 형식으로 넘겨줘야함!
		C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->CSSetShaderResources(M_tRegisterNumber, 1, &T_ShaderResourceView);		// Domain Shader에 쉐이더리소스 뷰 연결;
		M_uRegisterNumber = -1;
	}
	else
	{
		ID3D11ShaderResourceView* T_ShaderResourceView = nullptr;													// 유의! Component Object Model(COM)형식이므로, 뷰를 이중포인터 형식으로 넘겨줘야함!
		C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->CSSetShaderResources(_RegisterNumber, 1, &T_ShaderResourceView);		// Domain Shader에 쉐이더리소스 뷰 연결;
	}
}

void C_Texture::MF_Unbind_UnorderedAccessViewFromComputeByuRegister()
{
	UINT P_T_InitialCount = -1;				// 유의! 오버플로우로 최대값으로 초기 배열값을 최대로 주기 위한 트릭!; COM객체이므로, 이런 방식을 무조건 써야함!
	ID3D11UnorderedAccessView* T_UnorderedAccessView = nullptr;													// 유의! Component Object Model(COM)형식이므로, 뷰를 이중포인터 형식으로 넘겨줘야함!
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->CSSetUnorderedAccessViews(M_uRegisterNumber, 1, &T_UnorderedAccessView, &P_T_InitialCount);		// Domain Shader에 쉐이더리소스 뷰 연결;
}
