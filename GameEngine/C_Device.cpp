#include "pch.h"
#include "C_Device.h"

C_Device::C_Device()
    : M_H_Window(nullptr)
    , M_V2_RenderTargetResolution()

    , CP_M_DX_Device{}
    , CP_M_DX_DeviceContext{}

    , CP_M_DX_SwapChain{}

    , SP_M_DX_RenderTargetTexture{}
    , SP_M_DX_DepthStencilTexture{}
{
}

C_Device::~C_Device()
{

}

void C_Device::MF_Initialize(HWND _OutputWnd, Vector2 _vResolution)
{
    // DirectX Version Setting
    D3D_FEATURE_LEVEL level = D3D_FEATURE_LEVEL_11_0;

#ifdef _DEBUG
    // Device ������ Flag ���� - DEBUG���� �ƴ� ��� 0
    UINT SDK_T_Flag = D3D11_CREATE_DEVICE_DEBUG;

    // Device ����
    if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr
        , SDK_T_Flag, 0, 0, D3D11_SDK_VERSION
        , CP_M_DX_Device.GetAddressOf(), &level, CP_M_DX_DeviceContext.GetAddressOf()))) // ����, �ػ� ���� �κ� ��������
    {
        POPUP_DEBUG(L"FAILED(D3D11CreateDevice()", L"in C_Device::MF_Initialize(), FAILED(D3D11CreateDevice()");
    }

    // Swapchain ����
    if (FAILED(MF_Create_SwapChain()))
    {
        POPUP_DEBUG(L"FAILED(MF_Create_SwapChain()", L"in C_Device::MF_Initialize(), FAILED(MF_Create_SwapChain()");
    }

    // View ����
    if (FAILED(MF_Create_View()))
    {
        POPUP_DEBUG(L"FAILED(MF_Create_View()", L"in C_Device::MF_Initialize(), FAILED(MF_Create_View()");
    }

    // ����, ȭ�� ũ�� ������ �����ϴ� bool������ �ٽ� ���� �������� �ʰ� �ϴ� ���� �߰��� ���� ������ �ڵ� ��� ������ ��
    {

    }

#else
    UINT SDK_T_Flag = 0;

    // Device ����
    D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr
        , SDK_T_Flag, 0, 0, D3D11_SDK_VERSION
        , CP_M_DX_Device.GetAddressOf(), &level, CP_M_DX_DeviceContext.GetAddressOf());     // ����, �ػ� ���� �κ� ��������
    
    // Swapchain ����
    MF_Create_SwapChain();

    // View ����
    MF_Create_View();

    // ����, ȭ�� ũ�� ������ �����ϴ� bool������ �ٽ� ���� �������� �ʰ� �ϴ� ���� �߰��� ���� ������ �ڵ� ��� ������ ��
    {

    }
#endif // _DEBUG
}

HRESULT C_Device::MF_Clear_RanderTargetView()
{
	return E_NOTIMPL;
}

void C_Device::MF_Present()
{
#ifdef _DEBUG
    if (FAILED(CP_M_DX_SwapChain->Present(0, 0)))
    {
        POPUP(L"S_OK != CP_M_DX_SwapChain->Present(0, 0)", L"in C_Device::MF_Present(), S_OK != CP_M_DX_SwapChain->Present(0, 0)")
    }
#endif // _DEBUG

    CP_M_DX_SwapChain->Present(0, 0);
}

HRESULT C_Device::MF_Create_SwapChain()
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

HRESULT C_Device::MF_Create_View()
{
    // �� ���۷� ����� ���� ����
    ComPtr<ID3D11Texture2D> CP_T_DX_RenderTargetTexure = nullptr;

    // ����ü�� ������, �ڵ����� ���� ������� ����Ÿ�� ���۸� ������
    CP_M_DX_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)CP_T_DX_RenderTargetTexure.GetAddressOf());

    // SwapChain �� �����ϰ��ִ� ID3D11Texture2D ��ü�� CTexture Ŭ������ ��ȯ
    // C_Texture ����� Ȱ��ȭ�� ����
    // CP_M_DX_RenderTargetTexture = C_ResourceManager::MF_Get__Instance()->MF_CreateTexture(L"RenderTarget_Texure", CP_T_DX_RenderTargetTexure);

    // DepthStencil ���ҽ�(�ؽ���) ����
    // C_Texture ����� Ȱ��ȭ�� ����
    // CP_M_DX_DepthStencilTexture = C_ResourceManager::MF_Get__Instance()->MF_CreateTexture(L"DepthStencil_Texure"
        // , (UINT)M_V2_RenderTargetResolution.x, (UINT)M_V2_RenderTargetResolution.y
        // , DXGI_FORMAT_D24_UNORM_S8_UINT, D3D11_BIND_DEPTH_STENCIL);

    return S_OK;
}



HRESULT C_Device::MF_Create_ConstBuffer()
{
	return E_NOTIMPL;
}

HRESULT C_Device::MF_Create_RasterizerState()
{
	return E_NOTIMPL;
}

HRESULT C_Device::MF_Create_DepthStencilState()
{
	return E_NOTIMPL;
}

HRESULT C_Device::MF_Create_BlendState()
{
	return E_NOTIMPL;
}

HRESULT C_Device::MF_Create_SamplerState()
{
	return E_NOTIMPL;
}
