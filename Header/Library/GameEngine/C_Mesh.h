#pragma once
#include "C_Resource.h"

// 메쉬는 불변하도록 정한다
class C_Mesh :
    public C_Resource
{
public:
    C_Mesh();

public:
    C_Mesh(const C_Mesh& _Origin) = delete;

public:
    ~C_Mesh();

protected:
    // 향후, 버퍼값 내용을 플래그나, 구조체 형식으로 통일해서 캐싱하는 것이 어떨지에 대해 생각해보자
    DXGI_FORMAT                 DX_M_PerformanceFormat;           // DXGI_FORMAT; 정점 개수를 통해 퍼포먼스 및 메모리 조절용, 생성자로 기본 65535개 제한

    ComPtr<ID3D11Buffer>        CP_DX_M_VertexBuffer;             // ComPtr<ID3D11Buffer>
    D3D11_BUFFER_DESC           DX_M_VertexBufferDesc;         // D3D11_BUFFER_DESC
    UINT                        SDK_M_VertexCount;                // UINT
    DS_Vertex*                  P_DS_M_VertexSystemMemory;        // DS_Vertex*

    ComPtr<ID3D11Buffer>        CP_DX_M_IndexBuffer;              // ComPtr<ID3D11Buffer>
    D3D11_BUFFER_DESC           DX_M_IndexBufferDesc;          // D3D11_BUFFER_DESC
    UINT                        SDK_M_IndexCount;                 // UINT
    UINT*                       P_SDK_M_IndexSystemMemory;        // UINT*

public:
    void MF_Create_Buffer(DS_Vertex* _DS_VertexSystemMemory, UINT _SDK_VertexCount, UINT* _SDK_IndexSystemMemory, UINT _SDK_IndexCount);     // 가독성을 위해 NRVO 적용

    void MF_Render();                                       // 가독성을 위해 NRVO 적용

    void MF_ParticleRender(UINT _SDK_ParticleCount);        // 가독성을 위해 NRVO 적용; 향후, _SDK_ParticleCount를 캐싱하는 것도 고려해보자

public:
    // 바인딩함수; 향후, DXGI_FORMAT 값을 변경해서 정점 수 제한을 푸는 등 퍼포먼스 사용가능토록 고려해보자
    void MF_Bind();                                         // 가독성을 위해 NRVO 적용

public:
    DXGI_FORMAT MF_Get_DXGIFormat()
    {
        return DX_M_PerformanceFormat;
    }

    void MF_Set_DXGIFormat(DXGI_FORMAT _PerfomanceFormat)
    {
        DX_M_PerformanceFormat = _PerfomanceFormat;
    }

    // 향후, Save과 Load 구현


};

