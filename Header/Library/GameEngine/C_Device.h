#pragma once

#include"pch.h"

class C_Device: public C_Singleton<C_Device>
{
	// 싱글턴 매크로 안에 생성자와 소멸자 전부 정의
	SINGLE(C_Device)

private:
	HWND							MH_Window;
	Vector2							MV2_RenderTargetResolution;

	ComPtr<ID3D11Device>			CPMD_Device;
	ComPtr<ID3D11DeviceContext>		CPMD_Context;

	ComPtr<IDXGISwapChain>			CPMD_SwapChain;

	// 향후 정의예정
	// 기존 학습시 정의한 ptr 클래스는 이중포인터를 사용하기 위한 ComPtr의 열화판이고,
	// 이중포인터는 COM과 같은 DirectX 객체들에서만 쓰므로, 그냥 스마트 포인터로 전부 개조해서 쓰자
	// shared_ptr<CTexture>					SPMD_RenderTargetTexture;
	// shared_ptr<CTexture>					SPMD_DepthStencilTexture;

	// CConstBuffer* MD_ConstructureBuffer[(UINT)CB_TYPE::END];

	// ComPtr<ID3D11RasterizerState>			CPMEC_RasterizerState[(UINT)RASTERIZERSTATE_TYPE::END];
	// ComPtr<ID3D11DepthStencilState>			CPMEC_DepthStencilState[(UINT)DEPTHSTENCILSTATE_TYPE::END];
	// ComPtr<ID3D11BlendState>					CPMEC_BlendState[(UINT)BLENDSTATE_TYPE::END];

	ComPtr<ID3D11SamplerState>		CPMD_Sampler[2];

private:
	int MF_CreateSwapChain();
	int MF_CreateView();
	void MF_CreateConstBuffer();
	void MF_CreateRasterizerState();
	void MF_CreateDepthStencilState();
	void MF_CreateBlendState();
	void MF_CreateSamplerState();

public:
	int MF_Initialize(HWND _OutputWnd, Vector2 _vResolution);

	void MF_ClearTarget();
	void MF_Present();

	ComPtr<ID3D11Device> MF_GetDevice() { return CPMD_Device; }
	ComPtr<ID3D11DeviceContext> MF_GetContext() { return CPMD_Context; }
	// 향후 정의예정
	// C_ConstBuffer* MF_GetConstBuffer(CONSTRUCTUREBUFFER_TYPE _Type) { return MD_ConstructureBuffer[(UINT)_Type]; }
	// Vector2 MF_GetRenderResolution() { return MV2_RenderTargetResolution; }
	// ComPtr<ID3D11RasterizerState> MF_GetRSState(RASTERIZERSTATE_TYPE _Type) { return CPMEC_RasterizerState[(UINT)_Type]; }
	// ComPtr<ID3D11DepthStencilState> MF_GetDSState(DEPTHSTENCILSTATE_TYPE _Type) { return CPMEC_DepthStencilState[(UINT)_Type]; }
	// ComPtr<ID3D11BlendState>	MF_GetBSState(BLENDSTATE_TYPE _Type) { return CPMEC_BlendState[(UINT)_Type]; }
};