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

HRESULT C_Texture::MF_Set_Description(DXGI_FORMAT _Fomat, UINT _Width, UINT _Height, UINT _Flag, D3D11_USAGE _Usage)		// 그냥 여기서만 쓸 기본적인 함수
{
	M_D_TextureDesc.Format = _Fomat;								// 픽셀 포맷 지정
	M_D_TextureDesc.ArraySize = 1;									// 일반 텍스처 값 = 1
	M_D_TextureDesc.Width = _Width;									// 텍스처의 너비
	M_D_TextureDesc.Height = _Height;								// 텍스처의 높이
	M_D_TextureDesc.BindFlags = _Flag;								// 텍스처에 사용할 옵션 플래그; 대표적 플래그 -> D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE	| D3D11_BIND_UNORDERED_ACCESS

	M_D_TextureDesc.Usage = _Usage;									// 텍스처 사용 방식; D3D11_USAGE_DYNAMIC = CPU는 쓰기만 가능, GPU는 읽기만 가능 | D3D11_USAGE_IMMUTABLE = 생성 이후 절대 변경 불가! | D3D11_USAGE_STAGING = CPU와 GPU간 중간 저장소
	M_D_TextureDesc.CPUAccessFlags = 0;								// 상기의 Usage일 경우에만 사용가능한 트리거 플래그; D3D11_CPU_ACCESS_WRITE = CPU 쓰기 권한 부여
	 
	M_D_TextureDesc.MipLevels = 1;									// MIPMAP 사용관련; 해상도가 낮은 텍스처를 쓸 것인지 여부; 0 = 자동으로 밉맵 계산 | 1 = 사용하지 않음

	M_D_TextureDesc.SampleDesc.Count = 1;							// 멀티 샘플링 설정; MSAA x2, x4, x8
	M_D_TextureDesc.SampleDesc.Quality = 0;							// 샘플링 수준 설정;

	// 유의! D3D11_TEXTURE2D_DESC가 바뀌거나 하면, 무조건 Texture를 다시 만들어야 함
	HRESULT T_CreateTexture2D = C_Device::SF_Get_Instance()->MF_Get_Device()->CreateTexture2D(&M_D_TextureDesc, nullptr, CP_M_D_Texture2D.GetAddressOf());
	if (FAILED(T_CreateTexture2D))
	{
		POPUP_DEBUG(L"C_Texture::MF_Set_Description Failed", L"in C_Texture::MF_Set_Description, C_Device::SF_Get_Instance()->->MF_Get_Device()->CreateTexture2D() Failed")

		return E_FAIL;
	}

	// 뎁스 스텐실 뷰 생성; 유의! 다른 플래그와 섞어서 쓸 수 없이 단일로만 써야함!
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
		// 렌더 타겟 뷰 생성; 유의! D3D11_BIND_DEPTH_STENCIL과는 병행불가
		if (M_D_TextureDesc.BindFlags & D3D11_BIND_RENDER_TARGET)
		{
			HRESULT T_CreateRenderTargetView = C_Device::SF_Get_Instance()->MF_Get_Device()->CreateRenderTargetView(CP_M_D_Texture2D.Get(), nullptr, CP_M_D_RenderTagetView.GetAddressOf());
			if FAILED((T_CreateRenderTargetView))
			{
				POPUP_DEBUG(L"C_Texture::MF_Set_Description Failed", L"in C_Texture::MF_Set_Description, C_Device::SF_Get_Instance()->->MF_Get_Device()->CreateRenderTargetView() Failed")

					return E_FAIL;
			}
		}

		// 쉐이더 리소스 뷰 생성
		if (M_D_TextureDesc.BindFlags & D3D11_BIND_SHADER_RESOURCE)
		{
			HRESULT T_CreateShaderResourceView = C_Device::SF_Get_Instance()->MF_Get_Device()->CreateShaderResourceView(CP_M_D_Texture2D.Get(), nullptr, CP_M_D_ShaderResourceView.GetAddressOf());
			if FAILED((T_CreateShaderResourceView))
			{
				POPUP_DEBUG(L"C_Texture::MF_Set_Description Failed", L"in C_Texture::MF_Set_Description, C_Device::SF_Get_Instance()->MF_Get_Device()->CreateShaderResourceView() Failed")

					return E_FAIL;
			}
		}

		// 언오더 엑세스 뷰 생성
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

	// 유의! D3D11_TEXTURE2D_DESC가 바뀌거나 하면, 무조건 Texture를 다시 만들어야 함
	HRESULT T_CreateTexture2D = C_Device::SF_Get_Instance()->MF_Get_Device()->CreateTexture2D(&M_D_TextureDesc, nullptr, CP_M_D_Texture2D.GetAddressOf());
	if (FAILED(T_CreateTexture2D))
	{
		POPUP_DEBUG(L"C_Texture::MF_Set_Description(ComPtr<ID3D11Texture2D> _Texture) Failed", L"in C_Texture::MF_Set_Description, C_Device::SF_Get_Instance()->->MF_Get_Device()->CreateTexture2D() Failed")

			return E_FAIL;
	}

	// 뎁스 스텐실 뷰 생성; 유의! 다른 플래그와 섞어서 쓸 수 없이 단일로만 써야함!
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
		// 렌더 타겟 뷰 생성; 유의! D3D11_BIND_DEPTH_STENCIL과는 병행불가
		if (M_D_TextureDesc.BindFlags & D3D11_BIND_RENDER_TARGET)
		{
			HRESULT T_CreateRenderTargetView = C_Device::SF_Get_Instance()->MF_Get_Device()->CreateRenderTargetView(CP_M_D_Texture2D.Get(), nullptr, CP_M_D_RenderTagetView.GetAddressOf());
			if (FAILED(T_CreateRenderTargetView))
			{
				POPUP_DEBUG(L"C_Texture::MF_Set_Description(ComPtr<ID3D11Texture2D>) _Texture)", L"in C_Texture::MF_Set_Description, C_Device::SF_Get_Instance()->->MF_Get_Device()->CreateRenderTargetView() Failed")

					return E_FAIL;
			}
		}

		// 쉐이더 리소스 뷰 생성
		if (M_D_TextureDesc.BindFlags & D3D11_BIND_SHADER_RESOURCE)
		{
			HRESULT T_CreateShaderResourceView = C_Device::SF_Get_Instance()->MF_Get_Device()->CreateShaderResourceView(CP_M_D_Texture2D.Get(), nullptr, CP_M_D_ShaderResourceView.GetAddressOf());
			if (FAILED(T_CreateShaderResourceView))
			{
				POPUP_DEBUG(L"C_Texture::MF_Set_Description Failed", L"in C_Texture::MF_Set_Description, C_Device::SF_Get_Instance()->MF_Get_Device()->CreateShaderResourceView() Failed")

					return E_FAIL;
			}
		}

		// 언오더 엑세스 뷰 생성
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

	// 유의! D3D11_TEXTURE2D_DESC가 바뀌거나 하면, 무조건 Texture를 다시 만들어야 함
	HRESULT T_CreateTexture2D = C_Device::SF_Get_Instance()->MF_Get_Device()->CreateTexture2D(&M_D_TextureDesc, nullptr, CP_M_D_Texture2D.GetAddressOf());
	if (FAILED(T_CreateTexture2D))
	{
		POPUP_DEBUG(L"C_Texture::MF_Set_Description Failed(D3D11_TEXTURE2D_DESC _Description)", L"in C_Texture::MF_Set_Description, C_Device::SF_Get_Instance()->->MF_Get_Device()->CreateTexture2D() Failed")

			return E_FAIL;
	}

	// 뎁스 스텐실 뷰 생성; 유의! 다른 플래그와 섞어서 쓸 수 없이 단일로만 써야함!
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
		// 렌더 타겟 뷰 생성; 유의! D3D11_BIND_DEPTH_STENCIL과는 병행불가
		if (M_D_TextureDesc.BindFlags & D3D11_BIND_RENDER_TARGET)
		{
			HRESULT T_CreateRenderTargetView = C_Device::SF_Get_Instance()->MF_Get_Device()->CreateRenderTargetView(CP_M_D_Texture2D.Get(), nullptr, CP_M_D_RenderTagetView.GetAddressOf());
			if (FAILED(T_CreateRenderTargetView))
			{
				POPUP_DEBUG(L"C_Texture::MF_Set_Description(D3D11_TEXTURE2D_DESC _Description) _Texture)", L"in C_Texture::MF_Set_Description, C_Device::SF_Get_Instance()->->MF_Get_Device()->CreateRenderTargetView() Failed")

					return E_FAIL;
			}
		}

		// 쉐이더 리소스 뷰 생성
		if (M_D_TextureDesc.BindFlags & D3D11_BIND_SHADER_RESOURCE)
		{
			HRESULT T_CreateShaderResourceView = C_Device::SF_Get_Instance()->MF_Get_Device()->CreateShaderResourceView(CP_M_D_Texture2D.Get(), nullptr, CP_M_D_ShaderResourceView.GetAddressOf());
			if (FAILED(T_CreateShaderResourceView))
			{
				POPUP_DEBUG(L"C_Texture::MF_Set_Description(D3D11_TEXTURE2D_DESC _Description) Failed", L"in C_Texture::MF_Set_Description, C_Device::SF_Get_Instance()->MF_Get_Device()->CreateShaderResourceView() Failed")

					return E_FAIL;
			}
		}

		// 언오더 엑세스 뷰 생성
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