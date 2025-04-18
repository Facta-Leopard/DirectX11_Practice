#pragma once
#include "C_Resource.h"

#include "global.h"

class C_Texture :
    public C_Resource
{
public:
    C_Texture(E_RESOURCE_TYPE _RESOURCETYPE);

protected:
    C_Texture(const C_Texture&) = delete;             // C_Texture는 고유하여야 하므로, 복사생성자 작동 방지

public:
    ~C_Texture();

protected:
    // Resouce 관련
    //// Resource 로드 관련
    ScratchImage                        M_ScratchImage;                    // ScratchImage; ScratchImage 외부 라이브러리 이용; class이므로 초기화시 {}사용하여야 함.

    //// Resource 관리용
    ComPtr<ID3D11Texture2D>             CP_DX_M_Texture2D;                   // ComPtr<ID3D11Texture2D>; GPU Buffer
    D3D11_TEXTURE2D_DESC                DX_M_TextureDesc;                    // D3D11_TEXTURE2D_DESC; Texture FLag; 유의! 여기 구조체 정보에 따라 CPU 및 GPU가 텍스처를 대하는 방식이 달라짐

    // View 관리용
    //// Render 관련
    ComPtr<ID3D11DepthStencilView>      CP_DX_M_DepthStencilView;            // ComPtr<ID3D11DepthStencilView>; 깊이 관련
    ComPtr<ID3D11RenderTargetView>      CP_DX_M_RenderTagetView;             // ComPtr<ID3D11RenderTargetView>; 백 버퍼

    //// ShaderResource 전용
    ComPtr<ID3D11ShaderResourceView>    CP_DX_M_ShaderResourceView;          // ComPtr<ID3D11ShaderResourceView>
    int                                 M_tRegisterNumber;                  // int; 유의! 음수 값(-1)은 최근에 사용한 t레지스터가 없다는 의미!, 양수 값은 사용한 t레지스터 숫자를 나타냄

    //// UnorderedAccess 전용
    ComPtr<ID3D11UnorderedAccessView>   CP_DX_M_UnorderedAccessView;         // ComPtr<Id311UnorderedAccessView>; Texel로 쓰기 위한 용도
    int                                 M_uRegisterNumber;                  // int; 유의! 음수 값(-1)은 최근에 사용한 u레지스터가 없다는 의미!, 양수 값은 사용한 u레지스터 숫자를 나타냄

public:
    void MF_Bind_ShaderResourceViewToAllShadersBytRegister(int _RegisterNumber);              // 쉐이더리소스 뷰를 t레지스터에 바인딩하는 함수

    void MF_Bind_ShaderResourceViewToComputeShadersByuRegister(int _RegisterNumber);          // 쉐이더리소스 뷰를 u레지스터에 바인딩하는 함수

    void MF_Bind_UnorderedAccessViewToComputeShadersByuRegister(int _RegisterNumber);         // 언오더엑세스 뷰를 u레지스터에 바인딩하는 함수

    void MF_Unbind_ShaderResourceViewFromComputeBytRegister(int _RegisterNumber);             // 쉐이더리소스 뷰를 t레지스터에서 바인딩을 해제하는 함수; 유의! 노이즈텍스처를 쓰는 경우 때문에, 함수 안에 분기가 있음!

    void MF_Unbind_UnorderedAccessViewFromComputeByuRegister();                               // 언오더엑세스 뷰를 u레지스터에서 바인딩을 해제하는 함수

public:
    ComPtr<ID3D11Texture2D> MF_Get_Texture2D()                                                // Getter
    {
        return CP_DX_M_Texture2D;
    }

    D3D11_TEXTURE2D_DESC MF_Get_TextureDesc()                                                 // Getter
    {
        return DX_M_TextureDesc;
    }

    UINT MF_Get_TextureWidth()                                                                // Getter; Texture 너비 반환
    {
        return DX_M_TextureDesc.Width;
    }

    UINT MF_Get_TextureHeight()                                                               // Getter; Texture 높이 반환
    {
        return DX_M_TextureDesc.Height;
    }

    void MF_Set_TextureDesc(DXGI_FORMAT _Fomat, UINT _Width, UINT _Height,                    // Setter; Overload; Description 기본설정용
        UINT _Flag, D3D11_USAGE _Usage);

    void MF_Set_TextureDesc(ComPtr<ID3D11Texture2D> _Texture);                                // Setter; Overload; Texure를 받으면 Description를 복사하여 새롭게 뷰 생성

    void MF_Set_TextureDesc(D3D11_TEXTURE2D_DESC _Description);                               // Setter; Overload; Description를 받으면 새롭게 뷰 생성


    ComPtr<ID3D11DepthStencilView> MF_Get_DepthStencilView()
    {
        return CP_DX_M_DepthStencilView;
    }

    ComPtr<ID3D11RenderTargetView> MF_Get_RenderTargetView()
    {
        return CP_DX_M_RenderTagetView;
    }

    ComPtr<ID3D11ShaderResourceView> MF_Get_ShaderResourceView()
    {
        return CP_DX_M_ShaderResourceView;
    }
        
    int MF_Get_tRegisterNumber()
    {
        return M_tRegisterNumber;
    }
        
    ComPtr<ID3D11UnorderedAccessView> MF_Get_UnorderedAccessView()
    {
        return CP_DX_M_UnorderedAccessView;
    }
        
    int MF_Get_uRegisterNumber()
    {
        return M_uRegisterNumber;
    }
        

    // 향후, Save 및 Load 기능 구현예정
};

