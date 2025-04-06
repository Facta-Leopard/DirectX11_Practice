#include "pch.h"
#include "C_Device.h"

HRESULT C_Device::MF_Initialize(HWND _OutputWnd, Vector2 _vResolution)
{

    // Device ������ Flag ���� - DEBUG���� �ƴ� ��� 0
    UINT Flag = 0;
#ifdef _DEBUG
    Flag = D3D11_CREATE_DEVICE_DEBUG;
#endif
    D3D_FEATURE_LEVEL level = D3D_FEATURE_LEVEL_11_0; // DirectX Version Setting

    // Device ����
    if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr
        , Flag, 0, 0, D3D11_SDK_VERSION
        , CP_M_DX_Device.GetAddressOf(), &level, CP_M_DX_Context.GetAddressOf()))) // ����, �ػ� ���� �κ� ��������
    {
        POPUP_DEBUG(L"Device Creating Failed", L"in C_Device::MF_Initialize(), Failed");
        return E_FAIL;
    }

    // Swapchain ����
    if (FAILED(MF_CreateSwapChain()))
    {
        POPUP_DEBUG(L"Swapchain Creating Failed", L"in C_Device::MF_CreateSwapChain(), Failed");
        return E_FAIL;
    }

    // View ����
    if (FAILED(MF_CreateView()))
    {
        POPUP_DEBUG(L"View Creating Failed", L"in C_Device::MF_CreateSwapChain(), Failed");
        return E_FAIL;
    }

    // ȭ�� ũ�� ������ �����ϴ� bool������, �ٽ� ���� �������� �ʰ� �ϴ� ���� �߰��� ���� ������ �ڵ� ��� ������ ��
    {

    }

	return E_NOTIMPL;
}

HRESULT C_Device::MF_ClearTarget()
{
	return E_NOTIMPL;
}

HRESULT C_Device::MF_Present()
{
	return E_NOTIMPL;
}

HRESULT C_Device::MF_CreateSwapChain()
{
    // ����ü���� �����, �⺻������ ����Ÿ�� ���۰� ����
    DXGI_SWAP_CHAIN_DESC Desc = {};

    Desc.OutputWindow = M_H_Window;   // ������ ����ü���� �̹����� ��½�ų ������ ������
    Desc.Windowed = true;            // ������ ���, ��üȭ�� ���

    Desc.Flags = 0;
    Desc.SampleDesc.Count = 1;
    Desc.SampleDesc.Quality = 0;
    Desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    Desc.BufferCount = 1;             // ��� Buffer ����         
    Desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // Buffer �뵵
    Desc.BufferDesc.Width = (UINT)M_V2_RenderTargetResolution.x;
    Desc.BufferDesc.Height = (UINT)M_V2_RenderTargetResolution.y;
    Desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    Desc.BufferDesc.RefreshRate.Numerator = 60;
    Desc.BufferDesc.RefreshRate.Denominator = 1;
    Desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    Desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

    ComPtr<IDXGIDevice> T_pDevice = nullptr;
    ComPtr<IDXGIAdapter> T_pAdapter = nullptr;
    ComPtr<IDXGIFactory> T_pFactory = nullptr;

    CP_M_DX_Device->QueryInterface(__uuidof(IDXGIDevice), (void**)&T_pDevice);
    T_pDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&T_pAdapter);
    T_pAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&T_pFactory);

    if (FAILED(T_pFactory->CreateSwapChain(T_pDevice.Get(), &Desc, CP_M_DX_SwapChain.GetAddressOf())))
    {
        return E_FAIL;
    }

    return S_OK;
}

HRESULT C_Device::MF_CreateView()
{
    // �� ���۷� ����� ���� ����
    ComPtr<ID3D11Texture2D> CP_T_DX_RenderTargetTexure = nullptr;

    // ����ü�� ������, �ڵ����� ���� ������� ����Ÿ�� ���۸� ������
    CP_M_DX_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)CP_T_DX_RenderTargetTexure.GetAddressOf());

    // SwapChain �� �����ϰ��ִ� ID3D11Texture2D ��ü�� CTexture Ŭ������ ��ȯ
    // C_Texture ����� Ȱ��ȭ�� ����
    // CP_M_DX_RenderTargetTexture = C_ResourceManager::MF_GetInstance()->MF_CreateTexture(L"RenderTarget_Texure", CP_T_DX_RenderTargetTexure);

    // DepthStencil ���ҽ�(�ؽ���) ����
    // C_Texture ����� Ȱ��ȭ�� ����
    // CP_M_DX_DepthStencilTexture = C_ResourceManager::MF_GetInstance()->MF_CreateTexture(L"DepthStencil_Texure"
        // , (UINT)M_V2_RenderTargetResolution.x, (UINT)M_V2_RenderTargetResolution.y
        // , DXGI_FORMAT_D24_UNORM_S8_UINT, D3D11_BIND_DEPTH_STENCIL);

    return S_OK;
}

HRESULT C_Device::MF_CreateConstBuffer()
{
	return E_NOTIMPL;
}

HRESULT C_Device::MF_CreateRasterizerState()
{
	return E_NOTIMPL;
}

HRESULT C_Device::MF_CreateDepthStencilState()
{
	return E_NOTIMPL;
}

HRESULT C_Device::MF_CreateBlendState()
{
	return E_NOTIMPL;
}

HRESULT C_Device::MF_CreateSamplerState()
{
	return E_NOTIMPL;
}
