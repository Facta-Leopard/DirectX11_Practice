#include "pch.h"
#include "C_ConstantBuffer.h"

C_ConstantBuffer::C_ConstantBuffer()
	: C_Entity()

	, CP_DX_M_ConstantBuffer{}
	, DX_M_ConstantBufferDesc{}
	, E_M_ConstantBufferType{ _CONSTANTBUFFER_END }
{
}

C_ConstantBuffer::~C_ConstantBuffer()
{
}

void C_ConstantBuffer::MF_Create_ConstantBuffer(UINT _ElementSize, UINT _ElementCount, E_CONSTANTBUFFER_TYPE _BufferType)		// 코드개선: 기존의 기본값 0이 들어가는 건 상당히 위험한 행위였음! 유의! 래핑으로 가독성 및 유지보수성 증가!
{
	MF_Create_ConstantBuffer((UINT)(_ElementSize * _ElementCount), _BufferType);
}

void C_ConstantBuffer::MF_Create_ConstantBuffer(UINT _ByteWidth, E_CONSTANTBUFFER_TYPE _BufferType)
{
	if (0 == _ByteWidth)		// 방어코드; 향후, 나중에 디버깅 전용으로 전환하는 것도 생각해보자
	{
		POPUP(L"0 == _ByteWidth", L"in C_ConstantBuffer::MF_Create_ConstantBuffer(), 0 == _ByteWidth")
		return;
	}

	E_M_ConstantBufferType = _BufferType;

	// D3D11_BUFFER_DESC.ByteWidth; Constant Buffer 크기 설정
	DX_M_ConstantBufferDesc.ByteWidth = _ByteWidth;

	// D3D11_BUFFER_DESC.USAGE Usage; 사용방식 설정
	//// DEFAULT: GPU 전용
	//// DYNAMIC: CPU -> GPU 업로드용(업데이트 자주)
	//// IMMUTABLE : 초기화 후 절대 변경 안 됨
	//// STAGING : CPU만 접근 가능(디버깅용)
	DX_M_ConstantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;

	// D3D11_BUFFER_DESC.BindFlags; 바인딩 플래그(옵션)
	DX_M_ConstantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	// D3D11_BUFFER_DESC.CPUAccessFlags; CPU 접근 플래그(옵션)
	//// D3D11_CPU_ACCESS_WRITE: CPU가 쓰기 전용으로 접근
	//// D3D11_CPU_ACCESS_READ: CPU가 읽기 전용으로 접근
	//// 0: CPU 접근 불가 (GPU 전용)
	DX_M_ConstantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	// D3D11_BUFFER_DESC.MiscFlags; 잡다 기능 플래그(옵션)
	//// 생략가능

	// D3D11_BUFFER_DESC.StructureByteStride;
	//// 구조체 버퍼 전용
	//// 생략가능
	
	if (FAILED(C_Device::SF_Get_Instance()->MF_Get_Device()->CreateBuffer(&DX_M_ConstantBufferDesc, nullptr, CP_DX_M_ConstantBuffer.GetAddressOf())))	// 향후, 최적화가 진짜로 되는 것인지 확인하여야
	{
		POPUP_DEBUG(L"CreateBuffer() Failed", L"in C_ConstantBuffer::MF_Create_ConstantBuffer(), CreateBuffer() Failed")
	}
}

void C_ConstantBuffer::MF_Bind_ConstantBuffer()
{
	// Vertex Shader Set
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->VSSetConstantBuffers((UINT)E_M_ConstantBufferType, 1, CP_DX_M_ConstantBuffer.GetAddressOf());
	// Hull Shader Set
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->HSSetConstantBuffers((UINT)E_M_ConstantBufferType, 1, CP_DX_M_ConstantBuffer.GetAddressOf());
	// Domain Shader Set
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->DSSetConstantBuffers((UINT)E_M_ConstantBufferType, 1, CP_DX_M_ConstantBuffer.GetAddressOf());
	// Geometry Shader Set
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->GSSetConstantBuffers((UINT)E_M_ConstantBufferType, 1, CP_DX_M_ConstantBuffer.GetAddressOf());
	// Pixel Shader Set
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->PSSetConstantBuffers((UINT)E_M_ConstantBufferType, 1, CP_DX_M_ConstantBuffer.GetAddressOf());
}

void C_ConstantBuffer::MF_Bind_ConstantBufferToComputeShaderOnly()
{
	// Compute Shader Set
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->CSSetConstantBuffers((UINT)E_M_ConstantBufferType, 1, CP_DX_M_ConstantBuffer.GetAddressOf());
}

void C_ConstantBuffer::MF_Set_ConstantBufferByData(void* _DataType, UINT _ByteWidth)
{
	if (0 == _ByteWidth)		// 방어코드; 향후, 나중에 디버깅 전용으로 전환하는 것도 생각해보자
	{
		POPUP(L"0 == _ByteWidth", L"in C_ConstantBuffer::MF_Set_ConstantBufferByData(), 0 == _ByteWidth")
			return;
	}

	// 데이터 전송용 구조체
	D3D11_MAPPED_SUBRESOURCE DX_T_Data = {};

	// DeviceContext의 Map()으로 GPU에 Lock을 걸어 GPU 접근 방지 및 CPU가 데이터 접근
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->Map(CP_DX_M_ConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &DX_T_Data);

	// 메모리를 통으로 복사하는 빠른 복사방법
	memcpy(DX_T_Data.pData, _DataType, _ByteWidth);

	// DeviceContext의 Unmap()으로 GPU에 Lock을 풀어 CPU 접근 방지 및 GPU가 데이터 접근
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->Unmap(CP_DX_M_ConstantBuffer.Get(), 0);
}






