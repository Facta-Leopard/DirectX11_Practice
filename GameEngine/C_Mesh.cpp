#include "pch.h"
#include "C_Mesh.h"

C_Mesh::C_Mesh()
	: C_Resource(_RESOURCE_MESH)

	, DX_M_PerformanceFormat(DXGI_FORMAT_R16_UINT)

	, CP_DX_M_VertexBuffer{}
	, CP_DX_M_VertexBufferDesc{}
	, SDK_M_VertexCount(0)
	, P_DS_M_VertexSystemMemory{}

	, CP_DX_M_IndexBuffer{}
	, CP_DX_M_IndexBufferDesc{}
	, SDK_M_IndexCount(0)
	, P_SDK_M_IndexSystemMemory{}
{

}

C_Mesh::~C_Mesh()
{

}

void C_Mesh::MF_Create_Buffer(DS_Vertex* _P_DS_VertexSystemMemory, UINT _SDK_VertexCount, UINT* _SDK_IndexSystemMemory, UINT _SDK_IndexCount)		// �������� ���� NRVO ����
{
	SDK_M_VertexCount = _SDK_VertexCount;
	SDK_M_IndexCount = _SDK_IndexCount;
	
	// D3D11_BUFFER_DESC.ByteWidth; Vertex Buffer ũ�� ����
	CP_DX_M_VertexBufferDesc.ByteWidth = sizeof(CP_DX_M_VertexBuffer) * SDK_M_VertexCount;

	// D3D11_BUFFER_DESC.USAGE Usage; ����� ����
	//// DEFAULT: GPU ����
	//// DYNAMIC: CPU -> GPU ���ε��(������Ʈ ����)
	//// IMMUTABLE : �ʱ�ȭ �� ���� ���� �� ��
	//// STAGING : CPU�� ���� ����(������)
	CP_DX_M_VertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;

	// D3D11_BUFFER_DESC.BindFlags; ���ε� �÷���(�ɼ�)
	CP_DX_M_VertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	// D3D11_BUFFER_DESC.CPUAccessFlags; CPU ���� �÷���(�ɼ�)
	CP_DX_M_VertexBufferDesc.CPUAccessFlags = 0;

	// D3D11_BUFFER_DESC.MiscFlags; ��� ��� �÷���(�ɼ�)
	//// ��������
	
	// D3D11_BUFFER_DESC.StructureByteStride;
	//// ����ü ���� ����
	//// ��������

	// �ʱ� ������ ���ۿ� ����ü
	D3D11_SUBRESOURCE_DATA DX_T_Data = {};
	DX_T_Data.pSysMem = P_DS_M_VertexSystemMemory;		// DS_Vertex*�� Void*�� ����

	// Vertex Buffer ����
	C_Device::SF_Get_Instance()->MF_Get_Device()->CreateBuffer(&CP_DX_M_VertexBufferDesc, &DX_T_Data, CP_DX_M_VertexBuffer.GetAddressOf());

	// D3D11_BUFFER_DESC.ByteWidth; Index Buffer ũ�� ����
	CP_DX_M_IndexBufferDesc.ByteWidth = sizeof(UINT) * _SDK_IndexCount;

	// D3D11_BUFFER_DESC.USAGE Usage; ����� ����
	//// DEFAULT: GPU ����
	//// DYNAMIC: CPU -> GPU ���ε��(������Ʈ ����)
	//// IMMUTABLE : �ʱ�ȭ �� ���� ���� �� ��
	//// STAGING : CPU�� ���� ����(������)
	CP_DX_M_IndexBufferDesc.Usage = D3D11_USAGE_DEFAULT;

	// D3D11_BUFFER_DESC.BindFlags; ���ε� �÷���(�ɼ�)
	CP_DX_M_IndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	// D3D11_BUFFER_DESC.CPUAccessFlags; CPU ���� �÷���(�ɼ�)
	CP_DX_M_IndexBufferDesc.CPUAccessFlags = 0;

	// D3D11_BUFFER_DESC.MiscFlags; ��� ��� �÷���(�ɼ�)
	//// ��������

	// D3D11_BUFFER_DESC.StructureByteStride;
	//// ����ü ���� ����
	//// ��������

	DX_T_Data.pSysMem = _SDK_IndexSystemMemory;

	C_Device::SF_Get_Instance()->MF_Get_Device()->CreateBuffer(&CP_DX_M_IndexBufferDesc, &DX_T_Data, CP_DX_M_IndexBuffer.GetAddressOf());

	// System �޸𸮷� ������ ����
	P_DS_M_VertexSystemMemory = new DS_Vertex[SDK_M_VertexCount];
	P_SDK_M_IndexSystemMemory = new UINT[SDK_M_IndexCount];

	// ���� ����; for���� �ƴ� memcpy()
	memcpy(P_DS_M_VertexSystemMemory, _P_DS_VertexSystemMemory, (sizeof(DS_Vertex) * SDK_M_VertexCount));
	memcpy(P_SDK_M_IndexSystemMemory, _SDK_IndexSystemMemory, (sizeof(UINT) * SDK_M_IndexCount));
}

void C_Mesh::MF_Render()
{
	MF_Bind_MeshToBuffer();
	UINT SDK_T_StartIndexLocation = 0;
	INT  SDK_T_BaseVertexLocation = 0;
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->DrawIndexed(SDK_M_IndexCount, SDK_T_StartIndexLocation, SDK_T_BaseVertexLocation);
}

void C_Mesh::MF_ParticleRender(UINT _SDK_ParticleCount)		// �������� ���� NRVO ����; ����, _SDK_ParticleCount�� ĳ���ϴ� �͵� ����غ���
{
	MF_Bind_MeshToBuffer();
	// DrawIndexedInstanced�� ������ �� ����
	UINT SDK_T_StartIndexLocation    = 0;		// �ε��� ���ۿ��� ������ ��ġ
	INT  SDK_T_BaseVertexLocation    = 0;		// Offset
	UINT SDK_T_StartInstanceLocation = 0;		// Instancing ���� �ε���

	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->DrawIndexedInstanced(SDK_M_IndexCount
		, _SDK_ParticleCount, SDK_T_StartIndexLocation, SDK_T_BaseVertexLocation, SDK_T_StartInstanceLocation);
}

void C_Mesh::MF_Bind_MeshToBuffer()		// �������� ���� NRVO ����
{
	// DeviceContext Buffet�� ������ �� ����; �������� ���� ���⿡ ����ؼ� ��; ����, RVO�� �ϴ� ���� ����غ���
	UINT SDK_T_StartSlot = 0;								// �����ε���
	UINT SDK_T_BufferNumber = 1;							// ���ε��� ���� ��; ����, �ν��Ͻ��� �� �������� ����� ����(�ν��Ͻ� ��)�� �����غ���
	UINT SDK_T_Stride = sizeof(CP_DX_M_VertexBuffer);		// ���� ũ��
	UINT SDK_T_VertexOffset = 0;							// ����

	// DeviceContext�� Vertex Buffer �� ����
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->IASetVertexBuffers(SDK_T_StartSlot, SDK_T_BufferNumber
		, CP_DX_M_VertexBuffer.GetAddressOf(), &SDK_T_Stride, &SDK_T_VertexOffset);


	// DeviceContext�� Index Buffer �� ����
	UINT SDK_T_IndexOffset = 0;

	// DeviceContext�� Index Buffer�� ����; ���� ��������.. ���ؽ��� COM�̸鼭 �̰� �� �� ��������..
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->IASetIndexBuffer(CP_DX_M_IndexBuffer.Get(), DX_M_PerformanceFormat, SDK_T_IndexOffset);		// 
}

