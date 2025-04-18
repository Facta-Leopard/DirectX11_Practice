#pragma once
#include "C_Resource.h"

#include "global.h"

class C_Texture :
    public C_Resource
{
public:
    C_Texture(E_RESOURCE_TYPE _RESOURCETYPE);

protected:
    C_Texture(const C_Texture&) = delete;             // C_Texture�� �����Ͽ��� �ϹǷ�, ��������� �۵� ����

public:
    ~C_Texture();

protected:
    // Resouce ����
    //// Resource �ε� ����
    ScratchImage                        M_ScratchImage;                    // ScratchImage; ScratchImage �ܺ� ���̺귯�� �̿�; class�̹Ƿ� �ʱ�ȭ�� {}����Ͽ��� ��.

    //// Resource ������
    ComPtr<ID3D11Texture2D>             CP_DX_M_Texture2D;                   // ComPtr<ID3D11Texture2D>; GPU Buffer
    D3D11_TEXTURE2D_DESC                DX_M_TextureDesc;                    // D3D11_TEXTURE2D_DESC; Texture FLag; ����! ���� ����ü ������ ���� CPU �� GPU�� �ؽ�ó�� ���ϴ� ����� �޶���

    // View ������
    //// Render ����
    ComPtr<ID3D11DepthStencilView>      CP_DX_M_DepthStencilView;            // ComPtr<ID3D11DepthStencilView>; ���� ����
    ComPtr<ID3D11RenderTargetView>      CP_DX_M_RenderTagetView;             // ComPtr<ID3D11RenderTargetView>; �� ����

    //// ShaderResource ����
    ComPtr<ID3D11ShaderResourceView>    CP_DX_M_ShaderResourceView;          // ComPtr<ID3D11ShaderResourceView>
    int                                 M_tRegisterNumber;                  // int; ����! ���� ��(-1)�� �ֱٿ� ����� t�������Ͱ� ���ٴ� �ǹ�!, ��� ���� ����� t�������� ���ڸ� ��Ÿ��

    //// UnorderedAccess ����
    ComPtr<ID3D11UnorderedAccessView>   CP_DX_M_UnorderedAccessView;         // ComPtr<Id311UnorderedAccessView>; Texel�� ���� ���� �뵵
    int                                 M_uRegisterNumber;                  // int; ����! ���� ��(-1)�� �ֱٿ� ����� u�������Ͱ� ���ٴ� �ǹ�!, ��� ���� ����� u�������� ���ڸ� ��Ÿ��

public:
    void MF_Bind_ShaderResourceViewToAllShadersBytRegister(int _RegisterNumber);              // ���̴����ҽ� �並 t�������Ϳ� ���ε��ϴ� �Լ�

    void MF_Bind_ShaderResourceViewToComputeShadersByuRegister(int _RegisterNumber);          // ���̴����ҽ� �並 u�������Ϳ� ���ε��ϴ� �Լ�

    void MF_Bind_UnorderedAccessViewToComputeShadersByuRegister(int _RegisterNumber);         // ����������� �並 u�������Ϳ� ���ε��ϴ� �Լ�

    void MF_Unbind_ShaderResourceViewFromComputeBytRegister(int _RegisterNumber);             // ���̴����ҽ� �並 t�������Ϳ��� ���ε��� �����ϴ� �Լ�; ����! �������ؽ�ó�� ���� ��� ������, �Լ� �ȿ� �бⰡ ����!

    void MF_Unbind_UnorderedAccessViewFromComputeByuRegister();                               // ����������� �並 u�������Ϳ��� ���ε��� �����ϴ� �Լ�

public:
    ComPtr<ID3D11Texture2D> MF_Get_Texture2D()                                                // Getter
    {
        return CP_DX_M_Texture2D;
    }

    D3D11_TEXTURE2D_DESC MF_Get_TextureDesc()                                                 // Getter
    {
        return DX_M_TextureDesc;
    }

    UINT MF_Get_TextureWidth()                                                                // Getter; Texture �ʺ� ��ȯ
    {
        return DX_M_TextureDesc.Width;
    }

    UINT MF_Get_TextureHeight()                                                               // Getter; Texture ���� ��ȯ
    {
        return DX_M_TextureDesc.Height;
    }

    void MF_Set_TextureDesc(DXGI_FORMAT _Fomat, UINT _Width, UINT _Height,                    // Setter; Overload; Description �⺻������
        UINT _Flag, D3D11_USAGE _Usage);

    void MF_Set_TextureDesc(ComPtr<ID3D11Texture2D> _Texture);                                // Setter; Overload; Texure�� ������ Description�� �����Ͽ� ���Ӱ� �� ����

    void MF_Set_TextureDesc(D3D11_TEXTURE2D_DESC _Description);                               // Setter; Overload; Description�� ������ ���Ӱ� �� ����


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
        

    // ����, Save �� Load ��� ��������
};

