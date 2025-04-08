#pragma once
#include "C_Resource.h"

#include "global.h"

class C_Texture :
    public C_Resource
{
public:
    C_Texture(E_RESOURCE_TYPE _RESOURCETYPE);

public:
    ~C_Texture();

protected:
    // Resouce 관련
    //// Resource 로드 관련
    ScratchImage                        M_Scratch_Image;                    // ScratchImage; ScratchImage 외부 라이브러리 이용; class이므로 초기화시 {}사용하여야 함.

    //// Resource 관리용
    ComPtr<ID3D11Texture2D>             CP_M_D_Texture2D;                   // ComPtr<ID3D11Texture2D>; GPU Buffer
    D3D11_TEXTURE2D_DESC                M_D_TextureDesc;                    // D3D11_TEXTURE2D_DESC; Texture FLag

    // View 관리용
    //// Render 관련
    ComPtr<ID3D11RenderTargetView>      CP_M_D_RenderTagetView;             // ComPtr<ID3D11RenderTargetView>; 백 버퍼
    ComPtr<ID3D11DepthStencilView>      CP_M_D_DepthStencilView;            // ComPtr<ID3D11DepthStencilView>; 깊이 관련

    //// ShaderResource 전용
    ComPtr<ID3D11ShaderResourceView>    CP_M_D_ShaderResourceView;          // ComPtr<ID3D11ShaderResourceView>
    int                                 M_tRegisterNumber;              // int; 유의! 음수 값(-1)은 최근에 사용한 t레지스터가 없다는 의미!, 양수 값은 사용한 t레지스터 숫자를 나타냄

    //// UnorderedAccess 전용
    ComPtr<ID3D11UnorderedAccessView>   CP_M_D_UnorderedAccessView;         // ComPtr<Id311UnorderedAccessView>; Texel로 쓰기 위한 용도
    int                                 M_uRegisterNumber;              // int; 유의! 음수 값(-1)은 최근에 사용한 u레지스터가 없다는 의미!, 양수 값은 사용한 u레지스터 숫자를 나타냄

public:
    UINT MF_Get_TextureWidth()                                                                // Getter; Texture 너비 반환
    {
        return M_D_TextureDesc.Width;
    }

    UINT MF_Get_TextureHeight()                                                               // Getter; Texture 높이 반환
    {
        return M_D_TextureDesc.Height;
    }

protected:
    void MF_Bind_ShaderResourceViewToAllShadersBytRegister(int _RegisterNumber);              // 쉐이더리소스 뷰를 t레지스터에 바인딩하는 함수

    void MF_Bind_ShaderResourceViewToComputeShadersByuRegister(int _RegisterNumber);          // 쉐이더리소스 뷰를 u레지스터에 바인딩하는 함수

    void MF_Bind_UnorderedAccessViewToComputeShadersByuRegister(int _RegisterNumber);         // 언오더엑세스 뷰를 u레지스터에 바인딩하는 함수

    void MF_Unbind_ShaderResourceViewFromComputeBytRegister(int _RegisterNumber);             // 쉐이더리소스 뷰를 t레지스터에서 바인딩을 해제하는 함수; 유의! 노이즈텍스처를 쓰는 경우 때문에, 함수 안에 분기가 있음!

    void MF_Unbind_UnorderedAccessViewFromComputeByuRegister();                               // 언오더엑세스 뷰를 u레지스터에서 바인딩을 해제하는 함수



};

