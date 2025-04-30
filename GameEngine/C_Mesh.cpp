#include "pch.h"
#include "C_Mesh.h"

C_Mesh::C_Mesh()
	: C_Resource(_RESOURCE_MESH)

	, DX_M_PerformanceFormat(DXGI_FORMAT_R16_UINT)

	, CP_DX_M_VertexBuffer{}
	, DX_M_VertexBufferDesc{}
	, SDK_M_VertexCount(0)
	, P_DS_M_VertexSystemMemory{}

	, CP_DX_M_IndexBuffer{}
	, DX_M_IndexBufferDesc{}
	, SDK_M_IndexCount(0)
	, P_SDK_M_IndexSystemMemory{}
{

}

C_Mesh::~C_Mesh()
{

}

HRESULT C_Mesh::MF_Create_Buffer(DS_Vertex* _P_DS_VertexSystemMemory, UINT _SDK_VertexCount, UINT* _SDK_IndexSystemMemory, UINT _SDK_IndexCount)		// 가독성을 위해 NRVO 적용
{
	SDK_M_VertexCount = _SDK_VertexCount;
	SDK_M_IndexCount = _SDK_IndexCount;
	
	// D3D11_BUFFER_DESC.ByteWidth; Vertex Buffer 크기 설정
	DX_M_VertexBufferDesc.ByteWidth = sizeof(CP_DX_M_VertexBuffer) * SDK_M_VertexCount;

	// D3D11_BUFFER_DESC.USAGE Usage; 사용방식 설정
	//// DEFAULT: GPU 전용
	//// DYNAMIC: CPU -> GPU 업로드용(업데이트 자주)
	//// IMMUTABLE : 초기화 후 절대 변경 안 됨
	//// STAGING : CPU만 접근 가능(디버깅용)
	DX_M_VertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;

	// D3D11_BUFFER_DESC.BindFlags; 바인딩 플래그(옵션)
	//// D3D11_BIND_VERTEX_BUFFER: 버퍼를 Vertex Buffer로 사용
	//// D3D11_BIND_INDEX_BUFFER: 버퍼를 Index Buffer로 사용
	//// D3D11_BIND_CONSTANT_BUFFER: 버퍼를 Constant Buffer로 사용
	//// D3D11_BIND_SHADER_RESOURCE: 버퍼를 SRV(Shader Resource View: 텍스처 또는 구조 버퍼)로 사용
	//// D3D11_BIND_UNORDERED_ACCESS: 버퍼를 UAV(Unordered Access View: Compute Shader)로 사용
	DX_M_VertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	// D3D11_BUFFER_DESC.CPUAccessFlags; CPU 접근 플래그(옵션)
	//// D3D11_CPU_ACCESS_WRITE: CPU가 쓰기 전용으로 접근
	//// D3D11_CPU_ACCESS_READ: CPU가 읽기 전용으로 접근
	//// 0: CPU 접근 불가 (GPU 전용)
	DX_M_VertexBufferDesc.CPUAccessFlags = 0;

	// D3D11_BUFFER_DESC.MiscFlags; 잡다 기능 플래그(옵션)
	//// 생략가능
	
	// D3D11_BUFFER_DESC.StructureByteStride;
	//// 구조체 버퍼 전용
	//// 생략가능

	// 초기 데이터 전송용 구조체
	D3D11_SUBRESOURCE_DATA DX_T_Data = {};
	DX_T_Data.pSysMem = _P_DS_VertexSystemMemory;		// DS_Vertex*를 Void*로 대입

	// Vertex Buffer 생성
	HRESULT SDK_HRESULT_T_Vertexbuffer = C_Device::SF_Get_Instance()->MF_Get_Device()->CreateBuffer(&DX_M_VertexBufferDesc, &DX_T_Data, CP_DX_M_VertexBuffer.GetAddressOf());

	if (FAILED(SDK_HRESULT_T_Vertexbuffer))
	{
		POPUP(L"SDK_HRESULT_T_Vertexbuffer = C_Device::SF_Get_Instance()->MF_Get_Device()->CreateBuffer() Failed", L"in C_Mesh::MF_Create_Buffer(), SDK_HRESULT_T_Vertexbuffer = C_Device::SF_Get_Instance()->MF_Get_Device()->CreateBuffer() Failed")
		return E_FAIL;
	}

	// D3D11_BUFFER_DESC.ByteWidth; Index Buffer 크기 설정
	DX_M_IndexBufferDesc.ByteWidth = sizeof(UINT) * _SDK_IndexCount;

	// D3D11_BUFFER_DESC.USAGE Usage; 사용방식 설정
	//// DEFAULT: GPU 전용
	//// DYNAMIC: CPU -> GPU 업로드용(업데이트 자주)
	//// IMMUTABLE : 초기화 후 절대 변경 안 됨
	//// STAGING : CPU만 접근 가능(디버깅용)
	DX_M_IndexBufferDesc.Usage = D3D11_USAGE_DEFAULT;

	// D3D11_BUFFER_DESC.BindFlags; 바인딩 플래그(옵션)
	//// D3D11_BIND_VERTEX_BUFFER: 버퍼를 Vertex Buffer로 사용
	//// D3D11_BIND_INDEX_BUFFER: 버퍼를 Index Buffer로 사용
	//// D3D11_BIND_CONSTANT_BUFFER: 버퍼를 Constant Buffer로 사용
	//// D3D11_BIND_SHADER_RESOURCE: 버퍼를 SRV(Shader Resource View: 텍스처 또는 구조 버퍼)로 사용
	//// D3D11_BIND_UNORDERED_ACCESS: 버퍼를 UAV(Unordered Access View: Compute Shader)로 사용
	DX_M_IndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	// D3D11_BUFFER_DESC.CPUAccessFlags; CPU 접근 플래그(옵션)
	//// D3D11_CPU_ACCESS_WRITE: CPU가 쓰기 전용으로 접근
	//// D3D11_CPU_ACCESS_READ: CPU가 읽기 전용으로 접근
	//// 0: CPU 접근 불가 (GPU 전용)
	DX_M_IndexBufferDesc.CPUAccessFlags = 0;

	// D3D11_BUFFER_DESC.MiscFlags; 잡다 기능 플래그(옵션)
	//// 생략가능

	// D3D11_BUFFER_DESC.StructureByteStride;
	//// 구조체 버퍼 전용
	//// 생략가능

	DX_T_Data.pSysMem = _SDK_IndexSystemMemory;

	HRESULT SDK_HRESULT_T_Indexbuffer = C_Device::SF_Get_Instance()->MF_Get_Device()->CreateBuffer(&DX_M_IndexBufferDesc, &DX_T_Data, CP_DX_M_IndexBuffer.GetAddressOf());

	if (FAILED(SDK_HRESULT_T_Indexbuffer))
	{
		POPUP(L"SDK_HRESULT_T_Indexbuffer = C_Device::SF_Get_Instance()->MF_Get_Device()->CreateBuffer() Failed", L"in C_Mesh::MF_Create_Buffer(), SDK_HRESULT_T_Indexbuffer = C_Device::SF_Get_Instance()->MF_Get_Device()->CreateBuffer() Failed")
		return E_FAIL;
	}

	// System 메모리로 데이터 대입
	P_DS_M_VertexSystemMemory = new DS_Vertex[SDK_M_VertexCount];
	P_SDK_M_IndexSystemMemory = new UINT[SDK_M_IndexCount];

	// 빠른 복사; for문이 아닌 memcpy()
	memcpy(P_DS_M_VertexSystemMemory, _P_DS_VertexSystemMemory, (sizeof(DS_Vertex) * SDK_M_VertexCount));
	memcpy(P_SDK_M_IndexSystemMemory, _SDK_IndexSystemMemory, (sizeof(UINT) * SDK_M_IndexCount));

	return S_OK;
}

void C_Mesh::MF_Render()
{
	MF_Bind_Mesh();

	UINT SDK_T_StartIndexLocation = 0;
	INT  SDK_T_BaseVertexLocation = 0;
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->DrawIndexed(SDK_M_IndexCount, SDK_T_StartIndexLocation, SDK_T_BaseVertexLocation);
}

void C_Mesh::MF_ParticleRender(UINT _SDK_ParticleCount)		// 가독성을 위해 NRVO 적용; 향후, _SDK_ParticleCount를 캐싱하는 것도 고려해보자
{
	MF_Bind_Mesh();
	// DrawIndexedInstanced에 세팅할 값 설정
	UINT SDK_T_StartIndexLocation    = 0;		// 인덱스 버퍼에서 시작할 위치
	INT  SDK_T_BaseVertexLocation    = 0;		// Offset
	UINT SDK_T_StartInstanceLocation = 0;		// Instancing 시작 인덱스

	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->DrawIndexedInstanced(SDK_M_IndexCount
		, _SDK_ParticleCount, SDK_T_StartIndexLocation, SDK_T_BaseVertexLocation, SDK_T_StartInstanceLocation);
}

void C_Mesh::MF_Bind_Mesh()		// 가독성을 위해 NRVO 적용
{
	// DeviceContext Buffet에 세팅할 값 설정; 가독성을 위해 여기에 명시해서 씀; 향후, RVO로 하는 것을 고려해보자
	UINT SDK_T_StartSlot = 0;								// 시작인덱스
	UINT SDK_T_BufferNumber = 1;							// 바인딩할 버퍼 수; 향후, 인스턴싱할 때 여러개를 사용한 응용(인스턴싱 등)을 생각해보자
	UINT SDK_T_Stride = sizeof(CP_DX_M_VertexBuffer);		// 버퍼 크기
	UINT SDK_T_VertexOffset = 0;							// 간격

	// DeviceContext에 Vertex Buffer 값 설정
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->IASetVertexBuffers(SDK_T_StartSlot, SDK_T_BufferNumber
		, CP_DX_M_VertexBuffer.GetAddressOf(), &SDK_T_Stride, &SDK_T_VertexOffset);

	// DeviceContext에 Index Buffer 값 설정
	UINT SDK_T_IndexOffset = 0;

	// DeviceContext에 Index Buffer값 설정; 존나 그지같네.. 버텍스는 COM이면서 이건 왜 이 지랄이지..
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->IASetIndexBuffer(CP_DX_M_IndexBuffer.Get(), DX_M_PerformanceFormat, SDK_T_IndexOffset);		// 
}

