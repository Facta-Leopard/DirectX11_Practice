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
    // Device 생성용 Flag 설정 - DEBUG용이 아닌 경우 0
    UINT SDK_T_Flag = D3D11_CREATE_DEVICE_DEBUG;

    // Device 생성
    if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr
        , SDK_T_Flag, 0, 0, D3D11_SDK_VERSION
        , CP_M_DX_Device.GetAddressOf(), &level, CP_M_DX_DeviceContext.GetAddressOf()))) // 향후, 해상도 관련 부분 조정예정
    {
        POPUP_DEBUG(L"FAILED(D3D11CreateDevice()", L"in C_Device::MF_Initialize(), FAILED(D3D11CreateDevice()");
    }

    // Swapchain 생성
    if (FAILED(MF_Create_SwapChain()))
    {
        POPUP_DEBUG(L"FAILED(MF_Create_SwapChain()", L"in C_Device::MF_Initialize(), FAILED(MF_Create_SwapChain()");
    }

    // View 생성
    if (FAILED(MF_Create_View()))
    {
        POPUP_DEBUG(L"FAILED(MF_Create_View()", L"in C_Device::MF_Initialize(), FAILED(MF_Create_View()");
    }

    // 향후, 화면 크기 조정시 관여하는 bool값으로 다시 버퍼 생성하지 않게 하는 것을 추가할 수도 있으니 코드 블록 구분해 둠
    {

    }

#else
    UINT SDK_T_Flag = 0;

    // Device 생성
    D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr
        , SDK_T_Flag, 0, 0, D3D11_SDK_VERSION
        , CP_M_DX_Device.GetAddressOf(), &level, CP_M_DX_DeviceContext.GetAddressOf());     // 향후, 해상도 관련 부분 조정예정
    
    // Swapchain 생성
    MF_Create_SwapChain();

    // View 생성
    MF_Create_View();

    // 향후, 화면 크기 조정시 관여하는 bool값으로 다시 버퍼 생성하지 않게 하는 것을 추가할 수도 있으니 코드 블록 구분해 둠
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

HRESULT C_Device::MF_Create_View()
{
    // 백 버퍼로 사용할 버퍼 생성
    ComPtr<ID3D11Texture2D> CP_T_DX_RenderTargetTexure = nullptr;

    // 스왑체인 생성시, 자동으로 같이 만들어진 렌더타겟 버퍼를 가져옮
    CP_M_DX_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)CP_T_DX_RenderTargetTexure.GetAddressOf());

    // SwapChain 이 보유하고있는 ID3D11Texture2D 객체를 CTexture 클래스로 전환
    // C_Texture 만들고 활성화할 예정
    // CP_M_DX_RenderTargetTexture = C_ResourceManager::MF_Get__Instance()->MF_CreateTexture(L"RenderTarget_Texure", CP_T_DX_RenderTargetTexure);

    // DepthStencil 리소스(텍스쳐) 생성
    // C_Texture 만들고 활성화할 예정
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
