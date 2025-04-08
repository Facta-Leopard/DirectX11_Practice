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

void C_Texture::MF_Bind_ShaderResourceViewToAllShadersBytRegister(int _RegisterNumber)								// Graphic Pipeline�� ��� Shader�鿡 ShaderResource View ����
{
	// Pipeline : Vertex Shader(VS) -> Hull Shader(HS, Default) -> Domain Shader(DS, Default) -> Geometry Shader(GS, Default) -> Pixel Shader(PS)
	// Vertex Shader(VS) : ���� ��� �� UV��ǥ�� ����, Hull Shader(HS) : ��� �� �е� ���(Tessellator�� ����), Domain Shader(DS) : UV��ǥ ����, Geometry Shader(GS) : ���� �� ���� �����, Pixel Shader(PS) : �ȼ� ���(������ ����������, Texel �������� �������� ��� ����)
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->VSSetShaderResources(_RegisterNumber, 1, CP_M_D_ShaderResourceView.GetAddressOf());		// Vertex Shader�� ���̴����ҽ� �� ����;
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->HSSetShaderResources(_RegisterNumber, 1, CP_M_D_ShaderResourceView.GetAddressOf());		// Hull Shader�� ���̴����ҽ� �� ����;
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->DSSetShaderResources(_RegisterNumber, 1, CP_M_D_ShaderResourceView.GetAddressOf());		// Domain Shader�� ���̴����ҽ� �� ����;
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->GSSetShaderResources(_RegisterNumber, 1, CP_M_D_ShaderResourceView.GetAddressOf());		// Vertex Shader�� ���̴����ҽ� �� ����;
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->PSSetShaderResources(_RegisterNumber, 1, CP_M_D_ShaderResourceView.GetAddressOf());		// Vertex Shader�� ���̴����ҽ� �� ����;
}

void C_Texture::MF_Bind_ShaderResourceViewToComputeShadersByuRegister(int _RegisterNumber)
{
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->CSSetShaderResources(_RegisterNumber, 1, CP_M_D_ShaderResourceView.GetAddressOf());		// Domain Shader�� ���̴����ҽ� �� ����;
	M_tRegisterNumber = _RegisterNumber;
}

void C_Texture::MF_Bind_UnorderedAccessViewToComputeShadersByuRegister(int _RegisterNumber)
{
	UINT P_T_InitialCount = -1;				// ����! �����÷ο�� �ִ밪���� �ʱ� �迭���� �ִ�� �ֱ� ���� Ʈ��!; COM��ü�̹Ƿ�, �̷� ����� ������ �����!
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->CSSetUnorderedAccessViews(_RegisterNumber, 1, CP_M_D_UnorderedAccessView.GetAddressOf(), &P_T_InitialCount);	// Domain Shader�� ���̴����ҽ� �� ����;
	M_uRegisterNumber = _RegisterNumber;
}

void C_Texture::MF_Unbind_ShaderResourceViewFromComputeBytRegister(int _RegisterNumber)								// ����! �Լ� �� ������ �ٽ�ó ����� ���� �б⸦ ���!
{

	if (-1 == _RegisterNumber)
	{
		ID3D11ShaderResourceView* T_ShaderResourceView = nullptr;													// ����! Component Object Model(COM)�����̹Ƿ�, �並 ���������� �������� �Ѱ������!
		C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->CSSetShaderResources(M_tRegisterNumber, 1, &T_ShaderResourceView);		// Domain Shader�� ���̴����ҽ� �� ����;
		M_uRegisterNumber = -1;
	}
	else
	{
		ID3D11ShaderResourceView* T_ShaderResourceView = nullptr;													// ����! Component Object Model(COM)�����̹Ƿ�, �並 ���������� �������� �Ѱ������!
		C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->CSSetShaderResources(_RegisterNumber, 1, &T_ShaderResourceView);		// Domain Shader�� ���̴����ҽ� �� ����;
	}
}

void C_Texture::MF_Unbind_UnorderedAccessViewFromComputeByuRegister()
{
	UINT P_T_InitialCount = -1;				// ����! �����÷ο�� �ִ밪���� �ʱ� �迭���� �ִ�� �ֱ� ���� Ʈ��!; COM��ü�̹Ƿ�, �̷� ����� ������ �����!
	ID3D11UnorderedAccessView* T_UnorderedAccessView = nullptr;													// ����! Component Object Model(COM)�����̹Ƿ�, �並 ���������� �������� �Ѱ������!
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->CSSetUnorderedAccessViews(M_uRegisterNumber, 1, &T_UnorderedAccessView, &P_T_InitialCount);		// Domain Shader�� ���̴����ҽ� �� ����;
}
