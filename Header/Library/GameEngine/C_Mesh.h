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
    ComPtr<ID3D11Buffer>        CP_DX_M_VertexBuffer;             // ComPtr<ID3D11Buffer>
    D3D11_BUFFER_DESC           CP_DX_M_VertexBufferDesc;         // D3D11_BUFFER_DESC
    UINT                        SDK_M_VertexCount;                // UINT
    DS_Vertex*                  P_DS_M_VertexMemory;              // DS_Vertex*

    ComPtr<ID3D11Buffer>        CP_DX_M_IndexBuffer;              // ComPtr<ID3D11Buffer>
    D3D11_BUFFER_DESC           CP_DX_M_IndexBufferDesc;          // D3D11_BUFFER_DESC
    UINT                        SDK_M_IndexCount;                 // UINT
    UINT*                       P_SDK_M_IndexMemory;              // UINT*

public:
    void MF_Create_Buffer(DS_Vertex _VertexMemory, UINT _VertexCount, UINT* _IndexMemory, UINT _IndexCount);

    void MF_Render();

    void MF_ParticleRender();

public:
    void MF_Bind_MeshToBuffer();


    // ����, Save�� Load ����


};

