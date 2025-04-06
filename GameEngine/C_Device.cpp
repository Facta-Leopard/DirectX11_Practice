#include "pch.h"
#include "C_Device.h"

HRESULT C_Device::MF_Initialize(HWND _OutputWnd, Vector2 _vResolution)
{

    // Device 생성용 Flag 설정 - DEBUG용이 아닌 경우 0
    UINT Flag = 0;
#ifdef _DEBUG
    Flag = D3D11_CREATE_DEVICE_DEBUG;
#endif
    D3D_FEATURE_LEVEL level = D3D_FEATURE_LEVEL_11_0; // DirectX Version Setting

    // Device 생성
    if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr
        , Flag, 0, 0, D3D11_SDK_VERSION
        , CP_M_DX_Device.GetAddressOf(), &level, CP_M_DX_Context.GetAddressOf()))) // 향후, 해상도 관련 부분 조정예정
    {
        POPUP_DEBUG(L"Device Creating Failed", L"in C_Device::MF_Initialize(), Failed");
        return E_FAIL;
    }

    // Swapchain 생성
    if (FAILED(MF_CreateSwapChain()))
    {
        POPUP_DEBUG(L"Swapchain Creating Failed", L"in C_Device::MF_CreateSwapChain(), Failed");
        return E_FAIL;
    }

    // View 생성
    if (FAILED(MF_CreateView()))
    {
        POPUP_DEBUG(L"View Creating Failed", L"in C_Device::MF_CreateSwapChain(), Failed");
        return E_FAIL;
    }

    // 화면 크기 조정시 관여하는 bool값으로, 다시 버퍼 생성하지 않게 하는 것을 추가할 수도 있으니 코드 블록 구분해 둠
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
    // 스왑체인을 만들면, 기본적으로 렌더타겟 버퍼가 생김
    DXGI_SWAP_CHAIN_DESC Desc = {};

    Desc.OutputWindow = M_H_Window;   // 생성된 스왚체인이 이미지를 출력시킬 목적지 윈도우
    Desc.Windowed = true;            // 윈도우 모드, 전체화면 모드

    Desc.Flags = 0;
    Desc.SampleDesc.Count = 1;
    Desc.SampleDesc.Quality = 0;
    Desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    Desc.BufferCount = 1;             // 출력 Buffer 개수         
    Desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // Buffer 용도
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
    // 백 버퍼로 사용할 버퍼 생성
    ComPtr<ID3D11Texture2D> CP_T_DX_RenderTargetTexure = nullptr;

    // 스왑체인 생성시, 자동으로 같이 만들어진 렌더타겟 버퍼를 가져옮
    CP_M_DX_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)CP_T_DX_RenderTargetTexure.GetAddressOf());

    // SwapChain 이 보유하고있는 ID3D11Texture2D 객체를 CTexture 클래스로 전환
    // C_Texture 만들고 활성화할 예정
    // CP_M_DX_RenderTargetTexture = C_ResourceManager::MF_GetInstance()->MF_CreateTexture(L"RenderTarget_Texure", CP_T_DX_RenderTargetTexure);

    // DepthStencil 리소스(텍스쳐) 생성
    // C_Texture 만들고 활성화할 예정
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
