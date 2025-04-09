#pragma once

#include "global.h"
#include "C_Texture.h"

class C_Device: public C_Singleton<C_Device>
{
	// �̱��� ��ũ�� �ȿ� �����ڿ� �Ҹ��� ���� ����
	SINGLE(C_Device)

private:
	HWND									M_H_Window;													// HWND
	Vector2									M_V2_RenderTargetResolution;								// Vector2

	ComPtr<ID3D11Device>					CP_M_DX_Device;												// ComPtr<ID3D11Device>
	ComPtr<ID3D11DeviceContext>				CP_M_DX_DeviceContext;										// ComPtr<ID3D11DeviceContext>; ���� Ŭ������ �����Ϸ� ������, ������ ������ �ĺ��ڸ� ��Ī�� �ٲ�

	ComPtr<IDXGISwapChain>					CP_M_DX_SwapChain;											// ComPtr<IDXGISwapChain>

	// ���� �н��� ������ ptr Ŭ������ ���������͸� ����ϱ� ���� ComPtr�� ��ȭ���̰�,
	// ���������ʹ� COM�� ���� DirectX ��ü�鿡���� ���Ƿ�, �׳� ����Ʈ �����ͷ� ���� �����ؼ� ����
	shared_ptr<C_Texture>					SP_M_DX_RenderTargetTexture;
	shared_ptr<C_Texture>					SP_M_DX_DepthStencilTexture;

	// CConstBuffer* MD_ConstructureBuffer[(UINT)CB_TYPE::END];

	ComPtr<ID3D11RasterizerState>			CP_M_EC_RasterizerState[(UINT)_RASTERIZER_END];				// ComPtr<ID3D11RasterizerState>
	ComPtr<ID3D11DepthStencilState>			CP_M_EC_DepthStencilState[(UINT)_DEPTHSTENCIL_END];			// ComPtr<ID3D11DepthStencilState>
	ComPtr<ID3D11BlendState>				CP_M_EC_BlendState[(UINT)_BLEND_END];						// ComPtr<ID3D11BlendState>

	ComPtr<ID3D11SamplerState>				CP_M_DX_Sampler[2];											// ComPtr<ID3D11SamplerState>

	// WinAPI�� Ȱ���ϴϱ� ��������� ��ȯ���� HRESULT�� ��������
protected:
	HRESULT MF_Initialize(HWND _OutputWnd, Vector2 _vResolution);

	HRESULT MF_ClearTarget();
	HRESULT MF_Present();

public:
	inline ID3D11Device* MF_Get_Device()  																// Getter; ������ Device; CP_M_DX_Device.Get()
	{
		return CP_M_DX_Device.Get();
	}

	inline ID3D11DeviceContext* MF_Get_DeviceContext()  												// Getter; ������ DeviceContext; CP_M_DX_Device.Get()
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



	// ���� ���ǿ���
	// C_ConstBuffer* MF_Get_ConstBuffer(CONSTRUCTUREBUFFER_TYPE _Type) { return MD_ConstructureBuffer[(UINT)_Type]; }
	// Vector2 MF_Get_RenderResolution() { return MV2_RenderTargetResolution; }
	// ComPtr<ID3D11RasterizerState> MF_Get_RSState(RASTERIZERSTATE_TYPE _Type) { return CPMEC_RasterizerState[(UINT)_Type]; }
	// ComPtr<ID3D11DepthStencilState> MF_Get_DSState(DEPTHSTENCILSTATE_TYPE _Type) { return CPMEC_DepthStencilState[(UINT)_Type]; }
	// ComPtr<ID3D11BlendState>	MF_Get_BSState(BLENDSTATE_TYPE _Type) { return CPMEC_BlendState[(UINT)_Type]; }
};