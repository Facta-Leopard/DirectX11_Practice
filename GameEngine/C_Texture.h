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
    // Resouce ����
    //// Resource �ε� ����
    ScratchImage                        M_Scratch_Image;                    // ScratchImage; ScratchImage �ܺ� ���̺귯�� �̿�; class�̹Ƿ� �ʱ�ȭ�� {}����Ͽ��� ��.

    //// Resource ������
    ComPtr<ID3D11Texture2D>             CP_M_D_Texture2D;                   // ComPtr<ID3D11Texture2D>; GPU Buffer
    D3D11_TEXTURE2D_DESC                M_D_TextureDesc;                    // D3D11_TEXTURE2D_DESC; Texture FLag

    // View ������
    //// Render ����
    ComPtr<ID3D11RenderTargetView>      CP_M_D_RenderTagetView;             // ComPtr<ID3D11RenderTargetView>; �� ����
    ComPtr<ID3D11DepthStencilView>      CP_M_D_DepthStencilView;            // ComPtr<ID3D11DepthStencilView>; ���� ����

    //// ShaderResource ����
    ComPtr<ID3D11ShaderResourceView>    CP_M_D_ShaderResourceView;          // ComPtr<ID3D11ShaderResourceView>
    int                                 M_tRegisterNumber;              // int; ����! ���� ��(-1)�� �ֱٿ� ����� t�������Ͱ� ���ٴ� �ǹ�!, ��� ���� ����� t�������� ���ڸ� ��Ÿ��

    //// UnorderedAccess ����
    ComPtr<ID3D11UnorderedAccessView>   CP_M_D_UnorderedAccessView;         // ComPtr<Id311UnorderedAccessView>; Texel�� ���� ���� �뵵
    int                                 M_uRegisterNumber;              // int; ����! ���� ��(-1)�� �ֱٿ� ����� u�������Ͱ� ���ٴ� �ǹ�!, ��� ���� ����� u�������� ���ڸ� ��Ÿ��

public:
    UINT MF_Get_TextureWidth()                                                                // Getter; Texture �ʺ� ��ȯ
    {
        return M_D_TextureDesc.Width;
    }

    UINT MF_Get_TextureHeight()                                                               // Getter; Texture ���� ��ȯ
    {
        return M_D_TextureDesc.Height;
    }

protected:
    void MF_Bind_ShaderResourceViewToAllShadersBytRegister(int _RegisterNumber);              // ���̴����ҽ� �並 t�������Ϳ� ���ε��ϴ� �Լ�

    void MF_Bind_ShaderResourceViewToComputeShadersByuRegister(int _RegisterNumber);          // ���̴����ҽ� �並 u�������Ϳ� ���ε��ϴ� �Լ�

    void MF_Bind_UnorderedAccessViewToComputeShadersByuRegister(int _RegisterNumber);         // ����������� �並 u�������Ϳ� ���ε��ϴ� �Լ�

    void MF_Unbind_ShaderResourceViewFromComputeBytRegister(int _RegisterNumber);             // ���̴����ҽ� �並 t�������Ϳ��� ���ε��� �����ϴ� �Լ�; ����! �������ؽ�ó�� ���� ��� ������, �Լ� �ȿ� �бⰡ ����!

    void MF_Unbind_UnorderedAccessViewFromComputeByuRegister();                               // ����������� �並 u�������Ϳ��� ���ε��� �����ϴ� �Լ�



};

