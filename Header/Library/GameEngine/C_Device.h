#pragma once

#include"pch.h"

class C_Device: public C_Singleton<C_Device>
{
	// 싱글턴 매크로 안에 생성자와 소멸자 전부 정의
	SINGLE(C_Device)

private:
	HWND							M_H_Window;								// HWND
	Vector2							M_V2_RenderTargetResolution;			// Vector2

	ComPtr<ID3D11Device>			CP_M_DX_Device;							// ComPtr<ID3D11Device>
	ComPtr<ID3D11DeviceContext>		CP_M_DX_Context;							// ComPtr<ID3D11DeviceContext>

	ComPtr<IDXGISwapChain>			CP_M_DX_SwapChain;						// ComPtr<IDXGISwapChain>

	// 향후 C_Texture 정의예정
	// 기존 학습시 정의한 ptr 클래스는 이중포인터를 사용하기 위한 ComPtr의 열화판이고,
	// 이중포인터는 COM과 같은 DirectX 객체들에서만 쓰므로, 그냥 스마트 포인터로 전부 개조해서 쓰자
	// shared_ptr<C_Texture>					SP_M_DX_RenderTargetTexture;
	// shared_ptr<C_Texture>					SP_M_DX_DepthStencilTexture;

	// CConstBuffer* MD_ConstructureBuffer[(UINT)CB_TYPE::END];

	ComPtr<ID3D11RasterizerState>			CP_M_EC_RasterizerState[(UINT)_RASTERIZER_END];				// ComPtr<ID3D11RasterizerState>
	ComPtr<ID3D11DepthStencilState>			CP_M_EC_DepthStencilState[(UINT)_DEPTHSTENCIL_END];			// ComPtr<ID3D11DepthStencilState>
	ComPtr<ID3D11BlendState>				CP_M_EC_BlendState[(UINT)_BLEND_END];						// ComPtr<ID3D11BlendState>

	ComPtr<ID3D11SamplerState>				CP_M_DX_Sampler[2];											// ComPtr<ID3D11SamplerState>

	// WinAPI를 활용하니까 에러검출용 반환값인 HRESULT로 통일하자
public:
	HRESULT MF_Initialize(HWND _OutputWnd, Vector2 _vResolution);

	HRESULT MF_ClearTarget();
	HRESULT MF_Present();

private:
	HRESULT MF_CreateSwapChain();
	HRESULT MF_CreateView();
	HRESULT MF_CreateConstBuffer();
	HRESULT MF_CreateRasterizerState();
	HRESULT MF_CreateDepthStencilState();
	HRESULT MF_CreateBlendState();
	HRESULT MF_CreateSamplerState();

public:
	inline ComPtr<ID3D11Device> MF_GetDevice()												// Getter; CP_M_DX_Device
	{
		return CP_M_DX_Device;
	}
	inline ComPtr<ID3D11DeviceContext> MF_GetContext()										// Getter; CP_M_DX_Context
	{
		return CP_M_DX_Context;
	}

	// 향후 정의예정
	// C_ConstBuffer* MF_GetConstBuffer(CONSTRUCTUREBUFFER_TYPE _Type) { return MD_ConstructureBuffer[(UINT)_Type]; }
	// Vector2 MF_GetRenderResolution() { return MV2_RenderTargetResolution; }
	// ComPtr<ID3D11RasterizerState> MF_GetRSState(RASTERIZERSTATE_TYPE _Type) { return CPMEC_RasterizerState[(UINT)_Type]; }
	// ComPtr<ID3D11DepthStencilState> MF_GetDSState(DEPTHSTENCILSTATE_TYPE _Type) { return CPMEC_DepthStencilState[(UINT)_Type]; }
	// ComPtr<ID3D11BlendState>	MF_GetBSState(BLENDSTATE_TYPE _Type) { return CPMEC_BlendState[(UINT)_Type]; }
};