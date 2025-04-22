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

void C_ConstantBuffer::MF_Create_ConstantBuffer(UINT _ElementSize, UINT _ElementCount, E_CONSTANTBUFFER_TYPE _BufferType)		// �ڵ尳��: ������ �⺻�� 0�� ���� �� ����� ������ ��������! ����! �������� ������ �� ���������� ����!
{
	MF_Create_ConstantBuffer((UINT)(_ElementSize * _ElementCount), _BufferType);
}

void C_ConstantBuffer::MF_Create_ConstantBuffer(UINT _ByteWidth, E_CONSTANTBUFFER_TYPE _BufferType)
{
	if (0 == _ByteWidth)		// ����ڵ�; ����, ���߿� ����� �������� ��ȯ�ϴ� �͵� �����غ���
	{
		POPUP(L"0 == _ByteWidth", L"in C_ConstantBuffer::MF_Create_ConstantBuffer(), 0 == _ByteWidth")
		return;
	}

	E_M_ConstantBufferType = _BufferType;

	// D3D11_BUFFER_DESC.ByteWidth; Constant Buffer ũ�� ����
	DX_M_ConstantBufferDesc.ByteWidth = _ByteWidth;

	// D3D11_BUFFER_DESC.USAGE Usage; ����� ����
	//// DEFAULT: GPU ����
	//// DYNAMIC: CPU -> GPU ���ε��(������Ʈ ����)
	//// IMMUTABLE : �ʱ�ȭ �� ���� ���� �� ��
	//// STAGING : CPU�� ���� ����(������)
	DX_M_ConstantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;

	// D3D11_BUFFER_DESC.BindFlags; ���ε� �÷���(�ɼ�)
	DX_M_ConstantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	// D3D11_BUFFER_DESC.CPUAccessFlags; CPU ���� �÷���(�ɼ�)
	//// D3D11_CPU_ACCESS_WRITE: CPU�� ���� �������� ����
	//// D3D11_CPU_ACCESS_READ: CPU�� �б� �������� ����
	//// 0: CPU ���� �Ұ� (GPU ����)
	DX_M_ConstantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	// D3D11_BUFFER_DESC.MiscFlags; ��� ��� �÷���(�ɼ�)
	//// ��������

	// D3D11_BUFFER_DESC.StructureByteStride;
	//// ����ü ���� ����
	//// ��������
	
	if (FAILED(C_Device::SF_Get_Instance()->MF_Get_Device()->CreateBuffer(&DX_M_ConstantBufferDesc, nullptr, CP_DX_M_ConstantBuffer.GetAddressOf())))	// ����, ����ȭ�� ��¥�� �Ǵ� ������ Ȯ���Ͽ���
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
	if (0 == _ByteWidth)		// ����ڵ�; ����, ���߿� ����� �������� ��ȯ�ϴ� �͵� �����غ���
	{
		POPUP(L"0 == _ByteWidth", L"in C_ConstantBuffer::MF_Set_ConstantBufferByData(), 0 == _ByteWidth")
			return;
	}

	// ������ ���ۿ� ����ü
	D3D11_MAPPED_SUBRESOURCE DX_T_Data = {};

	// DeviceContext�� Map()���� GPU�� Lock�� �ɾ� GPU ���� ���� �� CPU�� ������ ����
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->Map(CP_DX_M_ConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &DX_T_Data);

	// �޸𸮸� ������ �����ϴ� ���� ������
	memcpy(DX_T_Data.pData, _DataType, _ByteWidth);

	// DeviceContext�� Unmap()���� GPU�� Lock�� Ǯ�� CPU ���� ���� �� GPU�� ������ ����
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->Unmap(CP_DX_M_ConstantBuffer.Get(), 0);
}






