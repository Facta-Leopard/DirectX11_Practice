#pragma once

#include "global.h"
#include "C_Texture.h"

class C_Device: public C_Singleton<C_Device>
{
	// 싱글턴 매크로 안에 생성자와 소멸자 전부 정의
	SINGLE(C_Device)

private:
	HWND									M_H_Window;													// HWND
	Vector2									M_V2_RenderTargetResolution;								// Vector2

	ComPtr<ID3D11Device>					CP_M_DX_Device;												// ComPtr<ID3D11Device>
	ComPtr<ID3D11DeviceContext>				CP_M_DX_DeviceContext;										// ComPtr<ID3D11DeviceContext>; 별도 클래스로 구성하려 했으나, 가독성 문제로 식별자만 명칭을 바꿈

	ComPtr<IDXGISwapChain>					CP_M_DX_SwapChain;											// ComPtr<IDXGISwapChain>

	// 기존 학습시 정의한 ptr 클래스는 이중포인터를 사용하기 위한 ComPtr의 열화판이고,
	// 이중포인터는 COM과 같은 DirectX 객체들에서만 쓰므로, 그냥 스마트 포인터로 전부 개조해서 쓰자
	shared_ptr<C_Texture>					SP_M_DX_RenderTargetTexture;
	shared_ptr<C_Texture>					SP_M_DX_DepthStencilTexture;

	// CConstBuffer* MD_ConstructureBuffer[(UINT)CB_TYPE::END];

	ComPtr<ID3D11RasterizerState>			CP_M_EC_RasterizerState[(UINT)_RASTERIZER_END];				// ComPtr<ID3D11RasterizerState>
	ComPtr<ID3D11DepthStencilState>			CP_M_EC_DepthStencilState[(UINT)_DEPTHSTENCIL_END];			// ComPtr<ID3D11DepthStencilState>
	ComPtr<ID3D11BlendState>				CP_M_EC_BlendState[(UINT)_BLEND_END];						// ComPtr<ID3D11BlendState>

	ComPtr<ID3D11SamplerState>				CP_M_DX_Sampler[2];											// ComPtr<ID3D11SamplerState>

	// WinAPI를 활용하니까 에러검출용 반환값인 HRESULT로 통일하자
protected:
	HRESULT MF_Initialize(HWND _OutputWnd, Vector2 _vResolution);

	HRESULT MF_ClearTarget();
	HRESULT MF_Present();

public:
	inline ID3D11Device* MF_Get_Device()  																// Getter; 생성된 Device; CP_M_DX_Device.Get()
	{
		return CP_M_DX_Device.Get();
	}

	inline ID3D11DeviceContext* MF_Get_DeviceContext()  												// Getter; 생성된 DeviceContext; CP_M_DX_Device.Get()
	{
		return CP_M_DX_DeviceContext.Get();
	}

protected:
	HRESULT MF_Create_SwapChain();

	HRESULT MF_Create_View();

	HRESULT MF_Create_ConstBuffer();

	HRESULT MF_Create_RasterizerState();

	HRESULT MF_Create_DepthStencilState();

	HRESULT MF_Create_BlendState();

	HRESULT MF_Create_SamplerState();



	// 향후 정의예정
	// C_ConstBuffer* MF_Get_ConstBuffer(CONSTRUCTUREBUFFER_TYPE _Type) { return MD_ConstructureBuffer[(UINT)_Type]; }
	// Vector2 MF_Get_RenderResolution() { return MV2_RenderTargetResolution; }
	// ComPtr<ID3D11RasterizerState> MF_Get_RSState(RASTERIZERSTATE_TYPE _Type) { return CPMEC_RasterizerState[(UINT)_Type]; }
	// ComPtr<ID3D11DepthStencilState> MF_Get_DSState(DEPTHSTENCILSTATE_TYPE _Type) { return CPMEC_DepthStencilState[(UINT)_Type]; }
	// ComPtr<ID3D11BlendState>	MF_Get_BSState(BLENDSTATE_TYPE _Type) { return CPMEC_BlendState[(UINT)_Type]; }
};