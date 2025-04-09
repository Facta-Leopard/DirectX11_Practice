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

HRESULT C_Texture::MF_Set_Description(DXGI_FORMAT _Fomat, UINT _Width, UINT _Height, UINT _Flag, D3D11_USAGE _Usage)		// �׳� ���⼭�� �� �⺻���� �Լ�
{
	M_D_TextureDesc.Format = _Fomat;								// �ȼ� ���� ����
	M_D_TextureDesc.ArraySize = 1;									// �Ϲ� �ؽ�ó �� = 1
	M_D_TextureDesc.Width = _Width;									// �ؽ�ó�� �ʺ�
	M_D_TextureDesc.Height = _Height;								// �ؽ�ó�� ����
	M_D_TextureDesc.BindFlags = _Flag;								// �ؽ�ó�� ����� �ɼ� �÷���; ��ǥ�� �÷��� -> D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE	| D3D11_BIND_UNORDERED_ACCESS

	M_D_TextureDesc.Usage = _Usage;									// �ؽ�ó ��� ���; D3D11_USAGE_DYNAMIC = CPU�� ���⸸ ����, GPU�� �б⸸ ���� | D3D11_USAGE_IMMUTABLE = ���� ���� ���� ���� �Ұ�! | D3D11_USAGE_STAGING = CPU�� GPU�� �߰� �����
	M_D_TextureDesc.CPUAccessFlags = 0;								// ����� Usage�� ��쿡�� ��밡���� Ʈ���� �÷���; D3D11_CPU_ACCESS_WRITE = CPU ���� ���� �ο�
	 
	M_D_TextureDesc.MipLevels = 1;									// MIPMAP ������; �ػ󵵰� ���� �ؽ�ó�� �� ������ ����; 0 = �ڵ����� �Ӹ� ��� | 1 = ������� ����

	M_D_TextureDesc.SampleDesc.Count = 1;							// ��Ƽ ���ø� ����; MSAA x2, x4, x8
	M_D_TextureDesc.SampleDesc.Quality = 0;							// ���ø� ���� ����;

	// ����! D3D11_TEXTURE2D_DESC�� �ٲ�ų� �ϸ�, ������ Texture�� �ٽ� ������ ��
	HRESULT T_CreateTexture2D = C_Device::SF_Get_Instance()->MF_Get_Device()->CreateTexture2D(&M_D_TextureDesc, nullptr, CP_M_D_Texture2D.GetAddressOf());
	if (FAILED(T_CreateTexture2D))
	{
		POPUP_DEBUG(L"C_Texture::MF_Set_Description Failed", L"in C_Texture::MF_Set_Description, C_Device::SF_Get_Instance()->->MF_Get_Device()->CreateTexture2D() Failed")

		return E_FAIL;
	}

	// ���� ���ٽ� �� ����; ����! �ٸ� �÷��׿� ��� �� �� ���� ���Ϸθ� �����!
	if (M_D_TextureDesc.BindFlags & D3D11_BIND_DEPTH_STENCIL)
	{
		HRESULT T_CreateDepthStencilView = C_Device::SF_Get_Instance()->MF_Get_Device()->CreateDepthStencilView(CP_M_D_Texture2D.Get(), nullptr, CP_M_D_DepthStencilView.GetAddressOf());
		if (FAILED(T_CreateDepthStencilView))
		{
			POPUP_DEBUG(L"C_Texture::MF_Set_Description Failed", L"in C_Texture::MF_Set_Description, C_Device::SF_Get_Instance()->MF_Get_Device()->CreateDepthStencilView() Failed")

				return E_FAIL;
		}
	}
	else
	{
		// ���� Ÿ�� �� ����; ����! D3D11_BIND_DEPTH_STENCIL���� ����Ұ�
		if (M_D_TextureDesc.BindFlags & D3D11_BIND_RENDER_TARGET)
		{
			HRESULT T_CreateRenderTargetView = C_Device::SF_Get_Instance()->MF_Get_Device()->CreateRenderTargetView(CP_M_D_Texture2D.Get(), nullptr, CP_M_D_RenderTagetView.GetAddressOf());
			if FAILED((T_CreateRenderTargetView))
			{
				POPUP_DEBUG(L"C_Texture::MF_Set_Description Failed", L"in C_Texture::MF_Set_Description, C_Device::SF_Get_Instance()->->MF_Get_Device()->CreateRenderTargetView() Failed")

					return E_FAIL;
			}
		}

		// ���̴� ���ҽ� �� ����
		if (M_D_TextureDesc.BindFlags & D3D11_BIND_SHADER_RESOURCE)
		{
			HRESULT T_CreateShaderResourceView = C_Device::SF_Get_Instance()->MF_Get_Device()->CreateShaderResourceView(CP_M_D_Texture2D.Get(), nullptr, CP_M_D_ShaderResourceView.GetAddressOf());
			if FAILED((T_CreateShaderResourceView))
			{
				POPUP_DEBUG(L"C_Texture::MF_Set_Description Failed", L"in C_Texture::MF_Set_Description, C_Device::SF_Get_Instance()->MF_Get_Device()->CreateShaderResourceView() Failed")

					return E_FAIL;
			}
		}

		// ����� ������ �� ����
		if (M_D_TextureDesc.BindFlags & D3D11_BIND_UNORDERED_ACCESS)
		{
			HRESULT T_CreateUnorderedAccessView = C_Device::SF_Get_Instance()->MF_Get_Device()->CreateUnorderedAccessView(CP_M_D_Texture2D.Get(), nullptr, CP_M_D_UnorderedAccessView.GetAddressOf());
			if FAILED((T_CreateUnorderedAccessView))
			{
				POPUP_DEBUG(L"C_Texture::MF_Set_Description Failed", L"in C_Texture::MF_Set_Description, C_Device::SF_Get_Instance()->MF_Get_Device()->CreateUnorderedAccessView() Failed")

					return E_FAIL;
			}
		}
	}

	return S_OK;
}

HRESULT C_Texture::MF_Set_Description(ComPtr<ID3D11Texture2D> _Texture)
{
	CP_M_D_Texture2D = _Texture;
	CP_M_D_Texture2D->GetDesc(&M_D_TextureDesc);

	// ����! D3D11_TEXTURE2D_DESC�� �ٲ�ų� �ϸ�, ������ Texture�� �ٽ� ������ ��
	HRESULT T_CreateTexture2D = C_Device::SF_Get_Instance()->MF_Get_Device()->CreateTexture2D(&M_D_TextureDesc, nullptr, CP_M_D_Texture2D.GetAddressOf());
	if (FAILED(T_CreateTexture2D))
	{
		POPUP_DEBUG(L"C_Texture::MF_Set_Description(ComPtr<ID3D11Texture2D> _Texture) Failed", L"in C_Texture::MF_Set_Description, C_Device::SF_Get_Instance()->->MF_Get_Device()->CreateTexture2D() Failed")

			return E_FAIL;
	}

	// ���� ���ٽ� �� ����; ����! �ٸ� �÷��׿� ��� �� �� ���� ���Ϸθ� �����!
	if (M_D_TextureDesc.BindFlags & D3D11_BIND_DEPTH_STENCIL)
	{
		HRESULT T_CreateDepthStencilView = C_Device::SF_Get_Instance()->MF_Get_Device()->CreateDepthStencilView(CP_M_D_Texture2D.Get(), nullptr, CP_M_D_DepthStencilView.GetAddressOf());
		if (FAILED(T_CreateDepthStencilView))
		{
			POPUP_DEBUG(L"C_Texture::MF_Set_Description(ComPtr<ID3D11Texture2D> _Texture) Failed", L"in C_Texture::MF_Set_Description, C_Device::SF_Get_Instance()->MF_Get_Device()->CreateDepthStencilView() Failed")

				return E_FAIL;
		}
	}
	else
	{
		// ���� Ÿ�� �� ����; ����! D3D11_BIND_DEPTH_STENCIL���� ����Ұ�
		if (M_D_TextureDesc.BindFlags & D3D11_BIND_RENDER_TARGET)
		{
			HRESULT T_CreateRenderTargetView = C_Device::SF_Get_Instance()->MF_Get_Device()->CreateRenderTargetView(CP_M_D_Texture2D.Get(), nullptr, CP_M_D_RenderTagetView.GetAddressOf());
			if (FAILED(T_CreateRenderTargetView))
			{
				POPUP_DEBUG(L"C_Texture::MF_Set_Description(ComPtr<ID3D11Texture2D>) _Texture)", L"in C_Texture::MF_Set_Description, C_Device::SF_Get_Instance()->->MF_Get_Device()->CreateRenderTargetView() Failed")

					return E_FAIL;
			}
		}

		// ���̴� ���ҽ� �� ����
		if (M_D_TextureDesc.BindFlags & D3D11_BIND_SHADER_RESOURCE)
		{
			HRESULT T_CreateShaderResourceView = C_Device::SF_Get_Instance()->MF_Get_Device()->CreateShaderResourceView(CP_M_D_Texture2D.Get(), nullptr, CP_M_D_ShaderResourceView.GetAddressOf());
			if (FAILED(T_CreateShaderResourceView))
			{
				POPUP_DEBUG(L"C_Texture::MF_Set_Description Failed", L"in C_Texture::MF_Set_Description, C_Device::SF_Get_Instance()->MF_Get_Device()->CreateShaderResourceView() Failed")

					return E_FAIL;
			}
		}

		// ����� ������ �� ����
		if (M_D_TextureDesc.BindFlags & D3D11_BIND_UNORDERED_ACCESS)
		{
			HRESULT T_CreateUnorderedAccessView = C_Device::SF_Get_Instance()->MF_Get_Device()->CreateUnorderedAccessView(CP_M_D_Texture2D.Get(), nullptr, CP_M_D_UnorderedAccessView.GetAddressOf());
			if FAILED((T_CreateUnorderedAccessView))
			{
				POPUP_DEBUG(L"C_Texture::MF_Set_Description Failed", L"in C_Texture::MF_Set_Description, C_Device::SF_Get_Instance()->MF_Get_Device()->CreateUnorderedAccessView() Failed")

					return E_FAIL;
			}
		}
	}

	return S_OK;
}

HRESULT C_Texture::MF_Set_Description(D3D11_TEXTURE2D_DESC _Description)
{
	M_D_TextureDesc = _Description;

	// ����! D3D11_TEXTURE2D_DESC�� �ٲ�ų� �ϸ�, ������ Texture�� �ٽ� ������ ��
	HRESULT T_CreateTexture2D = C_Device::SF_Get_Instance()->MF_Get_Device()->CreateTexture2D(&M_D_TextureDesc, nullptr, CP_M_D_Texture2D.GetAddressOf());
	if (FAILED(T_CreateTexture2D))
	{
		POPUP_DEBUG(L"C_Texture::MF_Set_Description Failed(D3D11_TEXTURE2D_DESC _Description)", L"in C_Texture::MF_Set_Description, C_Device::SF_Get_Instance()->->MF_Get_Device()->CreateTexture2D() Failed")

			return E_FAIL;
	}

	// ���� ���ٽ� �� ����; ����! �ٸ� �÷��׿� ��� �� �� ���� ���Ϸθ� �����!
	if (M_D_TextureDesc.BindFlags & D3D11_BIND_DEPTH_STENCIL)
	{
		HRESULT T_CreateDepthStencilView = C_Device::SF_Get_Instance()->MF_Get_Device()->CreateDepthStencilView(CP_M_D_Texture2D.Get(), nullptr, CP_M_D_DepthStencilView.GetAddressOf());
		if FAILED((T_CreateDepthStencilView))
		{
			POPUP_DEBUG(L"C_Texture::MF_Set_Description(D3D11_TEXTURE2D_DESC _Description) Failed", L"in C_Texture::MF_Set_Description, C_Device::SF_Get_Instance()->MF_Get_Device()->CreateDepthStencilView() Failed")

				return E_FAIL;
		}
	}
	else
	{
		// ���� Ÿ�� �� ����; ����! D3D11_BIND_DEPTH_STENCIL���� ����Ұ�
		if (M_D_TextureDesc.BindFlags & D3D11_BIND_RENDER_TARGET)
		{
			HRESULT T_CreateRenderTargetView = C_Device::SF_Get_Instance()->MF_Get_Device()->CreateRenderTargetView(CP_M_D_Texture2D.Get(), nullptr, CP_M_D_RenderTagetView.GetAddressOf());
			if (FAILED(T_CreateRenderTargetView))
			{
				POPUP_DEBUG(L"C_Texture::MF_Set_Description(D3D11_TEXTURE2D_DESC _Description) _Texture)", L"in C_Texture::MF_Set_Description, C_Device::SF_Get_Instance()->->MF_Get_Device()->CreateRenderTargetView() Failed")

					return E_FAIL;
			}
		}

		// ���̴� ���ҽ� �� ����
		if (M_D_TextureDesc.BindFlags & D3D11_BIND_SHADER_RESOURCE)
		{
			HRESULT T_CreateShaderResourceView = C_Device::SF_Get_Instance()->MF_Get_Device()->CreateShaderResourceView(CP_M_D_Texture2D.Get(), nullptr, CP_M_D_ShaderResourceView.GetAddressOf());
			if (FAILED(T_CreateShaderResourceView))
			{
				POPUP_DEBUG(L"C_Texture::MF_Set_Description(D3D11_TEXTURE2D_DESC _Description) Failed", L"in C_Texture::MF_Set_Description, C_Device::SF_Get_Instance()->MF_Get_Device()->CreateShaderResourceView() Failed")

					return E_FAIL;
			}
		}

		// ����� ������ �� ����
		if (M_D_TextureDesc.BindFlags & D3D11_BIND_UNORDERED_ACCESS)
		{
			HRESULT T_CreateUnorderedAccessView = C_Device::SF_Get_Instance()->MF_Get_Device()->CreateUnorderedAccessView(CP_M_D_Texture2D.Get(), nullptr, CP_M_D_UnorderedAccessView.GetAddressOf());
			if (FAILED(T_CreateUnorderedAccessView))
			{
				POPUP_DEBUG(L"C_Texture::MF_Set_Description(D3D11_TEXTURE2D_DESC _Description) Failed", L"in C_Texture::MF_Set_Description, C_Device::SF_Get_Instance()->MF_Get_Device()->CreateUnorderedAccessView() Failed")

					return E_FAIL;
			}
		}
	}

	return S_OK;
}