#pragma once
#include "C_Resource.h"

// �޽��� �Һ��ϵ��� ���Ѵ�
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
    // ����, ���۰� ������ �÷��׳�, ����ü �������� �����ؼ� ĳ���ϴ� ���� ����� ���� �����غ���
    DXGI_FORMAT                 DX_M_PerformanceFormat;           // DXGI_FORMAT; ���� ������ ���� �����ս� �� �޸� ������, �����ڷ� �⺻ 65535�� ����

    ComPtr<ID3D11Buffer>        CP_DX_M_VertexBuffer;             // ComPtr<ID3D11Buffer>
    D3D11_BUFFER_DESC           DX_M_VertexBufferDesc;         // D3D11_BUFFER_DESC
    UINT                        SDK_M_VertexCount;                // UINT
    DS_Vertex*                  P_DS_M_VertexSystemMemory;        // DS_Vertex*

    ComPtr<ID3D11Buffer>        CP_DX_M_IndexBuffer;              // ComPtr<ID3D11Buffer>
    D3D11_BUFFER_DESC           DX_M_IndexBufferDesc;          // D3D11_BUFFER_DESC
    UINT                        SDK_M_IndexCount;                 // UINT
    UINT*                       P_SDK_M_IndexSystemMemory;        // UINT*

public:
    void MF_Create_Buffer(DS_Vertex* _DS_VertexSystemMemory, UINT _SDK_VertexCount, UINT* _SDK_IndexSystemMemory, UINT _SDK_IndexCount);     // �������� ���� NRVO ����

    void MF_Render();                                       // �������� ���� NRVO ����

    void MF_ParticleRender(UINT _SDK_ParticleCount);        // �������� ���� NRVO ����; ����, _SDK_ParticleCount�� ĳ���ϴ� �͵� ����غ���

public:
    // ���ε��Լ�; ����, DXGI_FORMAT ���� �����ؼ� ���� �� ������ Ǫ�� �� �����ս� ��밡����� ����غ���
    void MF_Bind();                                         // �������� ���� NRVO ����

public:
    DXGI_FORMAT MF_Get_DXGIFormat()
    {
        return DX_M_PerformanceFormat;
    }

    void MF_Set_DXGIFormat(DXGI_FORMAT _PerfomanceFormat)
    {
        DX_M_PerformanceFormat = _PerfomanceFormat;
    }

    // ����, Save�� Load ����


};

