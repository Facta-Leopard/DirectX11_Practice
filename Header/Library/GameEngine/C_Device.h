#pragma once

#include "global.h"
#include "C_Texture.h"
#include "C_ConstantBuffer.h"
#include "C_Singleton.h"

class C_Device
	: public C_Singleton<C_Device>
{
	SINGLE(C_Device)

private:
	HWND									H_M_Window;													// HWND
	Vector2									VEC2_M_RenderTargetResolution;								// Vector2

	ComPtr<ID3D11Device>					CP_DX_M_Device;												// ComPtr<ID3D11Device>
	ComPtr<ID3D11DeviceContext>				CP_DX_M_DeviceContext;										// ComPtr<ID3D11DeviceContext>; ���� Ŭ������ �����Ϸ� ������, ������ ������ �ĺ��ڸ� ��Ī�� �ٲ�

	ComPtr<IDXGISwapChain>					CP_DX_M_SwapChain;											// ComPtr<IDXGISwapChain>

	// ���� �н��� ������ ptr Ŭ������ ���������͸� ����ϱ� ���� ComPtr�� ��ȭ���̰�,
	// ���������ʹ� COM�� ���� DirectX ��ü�鿡���� ���Ƿ�, �׳� ����Ʈ �����ͷ� ���� �����ؼ� ����
	shared_ptr<C_Texture>					SP_DX_M_RenderTargetTexture;								// shared_ptr<C_Texture>
	shared_ptr<C_Texture>					SP_DX_M_DepthStencilTexture;								// shared_ptr<C_Texture>

	C_ConstantBuffer*						P_M_ConstanctBuffer_s[(UINT)_CONSTANTBUFFER_END];			// C_ConstantBuffer*

	ComPtr<ID3D11RasterizerState>			CP_M_RasterizerState_s[(UINT)_RASTERIZER_END];				// ComPtr<ID3D11RasterizerState>
	ComPtr<ID3D11DepthStencilState>			CP_M_DepthStencilState_s[(UINT)_DEPTHSTENCIL_END];			// ComPtr<ID3D11DepthStencilState>
	ComPtr<ID3D11BlendState>				CP_M_BlendState_s[(UINT)_BLEND_END];						// ComPtr<ID3D11BlendState>

	ComPtr<ID3D11SamplerState>				CP_M_DX_SamplerType_s[_SAMPLER_END];						// ComPtr<ID3D11SamplerState>

	// WinAPI�� Ȱ���ϴϱ� ��������� ��ȯ���� HRESULT�� ��������

public:
	HRESULT MF_Initialize(HWND _OutputWnd, Vector2 _vResolution);

	void MF_ClearRenderTargetView();

	void MF_Present();
	
public:		// ����, Setter�� �δ� �Ͱ� �ƴ� ���� ���̸� �����غ���
	inline HWND MF_Get_WindowHandle()
	{
		return H_M_Window;
	}

	inline Vector2 MF_Get_RanderTargetResolution()
	{
		return	VEC2_M_RenderTargetResolution;
	}

	inline ID3D11Device* MF_Get_Device()  																// Getter; ������ Device; CP_M_DX_Device.Get()
	{
		return CP_DX_M_Device.Get();
	}

	inline ID3D11DeviceContext* MF_Get_DeviceContext()  												// Getter; ������ DeviceContext; CP_M_DX_Device.Get()
	{
		return CP_DX_M_DeviceContext.Get();
	}

	inline ComPtr<IDXGISwapChain> MF_Get_SwqpChain()
	{
		return CP_DX_M_SwapChain;
	}

	inline shared_ptr<C_Texture> MF_Get_RanderTargetTexture()
	{
		return SP_DX_M_RenderTargetTexture;
	}

	inline shared_ptr<C_Texture> MF_Get_DepthStencilTexture()
	{
		return SP_DX_M_DepthStencilTexture;
	}

	inline C_ConstantBuffer* MF_Get_ConstantBuffer(E_CONSTANTBUFFER_TYPE _E_ConstantBufferType)
	{
		return P_M_ConstanctBuffer_s[(UINT)_E_ConstantBufferType];
	}

	inline ComPtr<ID3D11RasterizerState> MF_Get_RasterizerState(E_RASTERIZER_STATE _RasterizerState)
	{
		return CP_M_RasterizerState_s[(UINT)_RasterizerState];
	}

	inline ComPtr<ID3D11DepthStencilState> MF_Get_DepthStencilState(E_DEPTHSTENCIL_STATE _DepthStencilState)
	{
		return CP_M_DepthStencilState_s[(UINT)_DepthStencilState];
	}

	inline ComPtr<ID3D11BlendState> MF_Get_BlendState(E_BLEND_STATE _BlendState)
	{
		return CP_M_BlendState_s[(UINT)_BlendState];
	}

protected:
	HRESULT MF_Create_SwapChain();

	HRESULT MF_Create_View();

	HRESULT MF_Create_ConstBuffer();

	HRESULT MF_Create_RasterizerState();

	HRESULT MF_Create_DepthStencilState();

	HRESULT MF_Create_BlendState();

	HRESULT MF_Create_SamplerState();

};