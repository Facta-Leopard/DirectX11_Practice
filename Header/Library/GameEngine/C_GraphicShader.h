#pragma once
#include "C_Resource.h"

class C_GraphicShader :
    public C_Resource
{
public:
    C_GraphicShader();

public:
    ~C_GraphicShader();

protected:
    // 에러처리용 비트바이트 구조체
    ComPtr<ID3DBlob>                    CP_DX_M_ErrorBlob;                  // ComPtr<ID3DBlob>

    // Graphic Pipeline
    //// IA: Input Assembler
    ComPtr<ID3D11InputLayout>           CP_DX_M_InputLayout;                // ComPtr<ID3D11InputLayout>
    D3D11_PRIMITIVE_TOPOLOGY            DX_M_PrimitiveTopology;             // D3D11_PRIMITIVE_TOPOLOGY

    //// VS: Vertex Shader
    ComPtr<ID3D11VertexShader>          CP_DX_M_VertexShader;               // ComPtr<ID3D11VertexShader>
    ComPtr<ID3DBlob>                    CP_DX_M_VertexShaderBlob;           // ComPtr<ID3DBlob>

    //// GS: Geometry Shader(optional)
    ComPtr<ID3D11GeometryShader>        CP_DX_M_GeometryShader;             // ComPtr<ID3D11GeometryShader>
    ComPtr<ID3DBlob>                    CP_DX_M_GeometryShaderBlob;         // ComPtr<ID3D11GeometryShader>

    //// RS: Rasterizer Stage
    E_RASTERIZER_STATE                  E_M_RasterizerState;                // E_RASTERIZER_TYPE; 기본값 -> _RASTERIZER_CULL_BACK

    //// PS: Pixel Shader
    ComPtr<ID3D11PixelShader>           CP_DX_M_PixelShader;                // ComPtr<ID3D11PixelShader>
    ComPtr<ID3DBlob>                    CP_DX_M_PixelShaderBlob;            // ComPtr<ID3DBlob>

    //// OM: Output Merger
    E_DEPTHSTENCIL_STATE                E_M_DepthStencilState;              // E_DEPTHSTENCIL_STATE
    E_BLEND_STATE                       E_M_BlendState;                     // E_BLEND_STATE; 기본값 -> _BLEND_DEFAULT

    // Domain
    E_DOMAIN_STATE                      E_M_DomainState;                    // E_DOMAIN_TYPE; 기본값 -> _DOMAIN_QPAQUE

public:
    void MF_Bind_GraphicShader();

public:
    void MF_Create_VertexShader(const wstring& _Path, const string& _HLSL_Function);

    void MF_Create_GeometryShader(const wstring& _Path, const string& _HLSL_Function);

    void MF_Create_PixelShader(const wstring& _Path, const string& _HLSL_Function);

public:
    // 유의! ID3DBlob같은 COM객체는 게터나 세터를 통한 멤버접근을 잘 하지 않음!
    inline D3D11_PRIMITIVE_TOPOLOGY MF_Get_Topology()
    {
        return DX_M_PrimitiveTopology;
    }

    inline E_RASTERIZER_STATE MF_Get_RasterizerState()
    {
        return E_M_RasterizerState;
    }

    inline E_DEPTHSTENCIL_STATE MF_Get_DepthStencilState()
    {
        return E_M_DepthStencilState;
    }

    inline E_BLEND_STATE MF_Get_BlendState()
    {
        return E_M_BlendState;
    }

    inline E_DOMAIN_STATE MF_Get_DomainState()
    {
        return E_M_DomainState;
    }

public:
    inline void MF_Set_Topology(D3D11_PRIMITIVE_TOPOLOGY _PrimitiveTopology)
    {
        DX_M_PrimitiveTopology = _PrimitiveTopology;
    }

    inline void MF_Set_RasterizerState(E_RASTERIZER_STATE _RasterizeState)
    {
        E_M_RasterizerState = _RasterizeState;
    }

    inline void MF_Set_DepthStencilState(E_DEPTHSTENCIL_STATE _DepthStencilState)
    {
        E_M_DepthStencilState = _DepthStencilState;
    }

    inline void MF_Set_BlendState(E_BLEND_STATE _BlendState)
    {
        E_M_BlendState = _BlendState;
    }

    inline void MF_Set_DomainType(E_DOMAIN_STATE _DomainState)
    {
        E_M_DomainState = _DomainState;
    }


};

