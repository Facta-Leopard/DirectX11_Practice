#include "pch.h"
#include "C_StructuredBuffer.h"

C_StructuredBuffer::C_StructuredBuffer()
	: C_Entity{}

	, CP_DX_M_StructuredBufferForTransfer{}
	, CP_DX_M_StructuredBufferForWriting{}
	, CP_DX_M_StructuredBufferForReading{}

	, DX_M_StructuredBufferDesc{}
	, E_M_StructuredBuffeType(_STRUCTUREDBUFFER_SHADERRESOURCEVIEW_ONLY)

	, CP_DX_M_ShaderResourceView{}
	, CP_DX_M_UnorderedAccessView{}

	, SDK_M_ElementSize(0)
	, SDK_M_ElementCount(0)

	, SDK_M_tRegisterNumberForComputeShader(0)
	, SDK_M_uRegisterNumberForComputeShader(0)
{
}

C_StructuredBuffer::~C_StructuredBuffer()
{
}

void C_StructuredBuffer::MF_Create_StructuredBuffer(UINT _ElementSize, UINT _ElementCount, E_STRUCTUREDBUFFER_TYPE _StructuredBufferType, void* _Data)
{
	CP_DX_M_StructuredBufferForTransfer = nullptr;
	CP_DX_M_StructuredBufferForWriting = nullptr;
	CP_DX_M_StructuredBufferForReading = nullptr;

	CP_DX_M_ShaderResourceView = nullptr;
	CP_DX_M_UnorderedAccessView = nullptr;

	E_M_StructuredBuffeType = _StructuredBufferType;

	// GPU �޸�ũ�� ����; ����! GPU�� �޸� ���������� 16 ����̹Ƿ� ������� ��!
	if (0 != ((_ElementSize * _ElementCount) % 16))		// �ڵ尳��; ��������� �ƴ� ���ڸ� �Ἥ �������� ������ ���� CPU ����Ŭ�� ����
	{
		POPUP(L"0 != ((SDK_M_ElementSize * SDK_M_ElementCount) % 16)", L"in C_StructuredBuffer::MF_Create_StructuredBuffer, 0 != ((SDK_M_ElementSize * SDK_M_ElementCount) % 16)")
	}

	SDK_M_ElementSize = _ElementSize;
	SDK_M_ElementCount = _ElementCount;

	// ���� ��ü �뷮
	DX_M_StructuredBufferDesc.ByteWidth = SDK_M_ElementSize * SDK_M_ElementCount;

	// ���� ���۴� SystemMem �� ��� �Ұ���
	DX_M_StructuredBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	DX_M_StructuredBufferDesc.CPUAccessFlags = 0;

	// ������ ��� ũ��(����)
	DX_M_StructuredBufferDesc.StructureByteStride = SDK_M_ElementSize;

	// ����ȭ���� ���� �÷���
	DX_M_StructuredBufferDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;

	// �뵵
	switch (_StructuredBufferType)
	{
	case _STRUCTUREDBUFFER_SHADERRESOURCEVIEW_ONLY:
		DX_M_StructuredBufferDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		break;
	case _STRUCTUREDBUFFER_UNORDEREDACCESSVIEW_ADDED:
		DX_M_StructuredBufferDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
		break;
	}

	// ���� ���� ����
	HRESULT SDK_T_HResult = S_OK;
	if (nullptr == _Data)
	{
		SDK_T_HResult = C_Device::SF_Get_Instance()->MF_Get_Device()->CreateBuffer(&DX_M_StructuredBufferDesc, nullptr, CP_DX_M_StructuredBufferForTransfer.GetAddressOf());
	}
	else
	{
		D3D11_SUBRESOURCE_DATA DX_T_SubResourceData = {};
		DX_T_SubResourceData.pSysMem = _Data;
		SDK_T_HResult = C_Device::SF_Get_Instance()->MF_Get_Device()->CreateBuffer(&DX_M_StructuredBufferDesc, &DX_T_SubResourceData, CP_DX_M_StructuredBufferForTransfer.GetAddressOf());
	}

	switch (_StructuredBufferType)		// ����! �� ������ ������ ���� ���� �Ŀ� �Ǿ�� �ϹǷ�, ���� ����ġ���� ��ĥ �� ����!; ����, �б⹮ ������ ���� ����� ������ ����غ���
	{
	case _STRUCTUREDBUFFER_UNORDEREDACCESSVIEW_ADDED:
		// u �������� ���ε��������� �� UnorderedAccessView ����
		D3D11_UNORDERED_ACCESS_VIEW_DESC DX_T_UnorderedAccessViewDesc = {};

		DX_T_UnorderedAccessViewDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
		DX_T_UnorderedAccessViewDesc.Buffer.NumElements = _ElementCount;

		if (FAILED(C_Device::SF_Get_Instance()->MF_Get_Device()->CreateUnorderedAccessView(CP_DX_M_StructuredBufferForTransfer.Get(), &DX_T_UnorderedAccessViewDesc, CP_DX_M_UnorderedAccessView.GetAddressOf())))
		{
			POPUP_DEBUG(L"CreateUnorderedAccessView() Failed", L"in C_StructuredBuffer::MF_Create_StructuredBuffer(), CreateUnorderedAccessView() Failed")
		}
	}


	if (FAILED(SDK_T_HResult))
	{
		POPUP_DEBUG(L"CreateBuffer() Failed", L"in C_StructuredBuffer::MF_Create_StructuredBuffer(), CreateBuffer() Failed")
	}

	// t �������� ���ε���, ShaderResourceView ����
	D3D11_SHADER_RESOURCE_VIEW_DESC DX_T_ShaderResourceViewDesc = {};

	DX_T_ShaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
	DX_T_ShaderResourceViewDesc.Buffer.NumElements = _ElementCount;

	if (FAILED(C_Device::SF_Get_Instance()->MF_Get_Device()->CreateShaderResourceView(CP_DX_M_StructuredBufferForTransfer.Get(), &DX_T_ShaderResourceViewDesc, CP_DX_M_ShaderResourceView.GetAddressOf())))
	{
		POPUP_DEBUG(L"CreateShaderResourceView() Failed", L"in C_StructuredBuffer::MF_Create_StructuredBuffer(), CreateShaderResourceView() Failed")
	}

	// UAV �߰� ����

	switch (_StructuredBufferType)
	{
	case _STRUCTUREDBUFFER_UNORDEREDACCESSVIEW_ADDED:
		D3D11_BUFFER_DESC DX_T_WriteBufferDesc = {};
		DX_T_WriteBufferDesc.ByteWidth = SDK_M_ElementSize * SDK_M_ElementCount;
		DX_T_WriteBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		DX_T_WriteBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		DX_T_WriteBufferDesc.StructureByteStride = SDK_M_ElementSize;
		DX_T_WriteBufferDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		DX_T_WriteBufferDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

		SDK_T_HResult = C_Device::SF_Get_Instance()->MF_Get_Device()->CreateBuffer(&DX_T_WriteBufferDesc, nullptr, CP_DX_M_StructuredBufferForWriting.GetAddressOf());


		D3D11_BUFFER_DESC DX_T_ReadBufferDesc = {};
		DX_T_ReadBufferDesc.ByteWidth = SDK_M_ElementSize * SDK_M_ElementCount;
		DX_T_ReadBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		DX_T_ReadBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
		DX_T_ReadBufferDesc.StructureByteStride = SDK_M_ElementSize;
		DX_T_ReadBufferDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		DX_T_ReadBufferDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

		SDK_T_HResult = C_Device::SF_Get_Instance()->MF_Get_Device()->CreateBuffer(&DX_T_ReadBufferDesc, nullptr, CP_DX_M_StructuredBufferForReading.GetAddressOf());
		break;
	}
}

void C_StructuredBuffer::MF_Bind_StructuredBuffer(UINT _RegisterNumber)
{
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->VSSetShaderResources(_RegisterNumber, 1, CP_DX_M_ShaderResourceView.GetAddressOf());
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->HSSetShaderResources(_RegisterNumber, 1, CP_DX_M_ShaderResourceView.GetAddressOf());
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->DSSetShaderResources(_RegisterNumber, 1, CP_DX_M_ShaderResourceView.GetAddressOf());
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->GSSetShaderResources(_RegisterNumber, 1, CP_DX_M_ShaderResourceView.GetAddressOf());
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->PSSetShaderResources(_RegisterNumber, 1, CP_DX_M_ShaderResourceView.GetAddressOf());
}

void C_StructuredBuffer::MF_Clear_StructuredBuffer(UINT _RegisterNumber)
{
	ID3D11ShaderResourceView* P_DX_ShaderResourceView = nullptr;
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->VSSetShaderResources(_RegisterNumber, 1, &P_DX_ShaderResourceView);
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->HSSetShaderResources(_RegisterNumber, 1, &P_DX_ShaderResourceView);
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->DSSetShaderResources(_RegisterNumber, 1, &P_DX_ShaderResourceView);
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->GSSetShaderResources(_RegisterNumber, 1, &P_DX_ShaderResourceView);
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->PSSetShaderResources(_RegisterNumber, 1, &P_DX_ShaderResourceView);
}

void C_StructuredBuffer::MF_Bind_StructuredBufferForComputingWithShaderResourceView(UINT _RegisterNumberForComputeShader)
{
	SDK_M_tRegisterNumberForComputeShader = _RegisterNumberForComputeShader;
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->CSSetShaderResources(_RegisterNumberForComputeShader
		, 1, CP_DX_M_ShaderResourceView.GetAddressOf());
}

void C_StructuredBuffer::MF_Clear_StructuredBufferForComputingWithShaderResourceView()
{
	ID3D11ShaderResourceView* P_DX_T_ShaderResourceView = nullptr;
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->CSSetShaderResources(SDK_M_tRegisterNumberForComputeShader, 1, &P_DX_T_ShaderResourceView);
	SDK_M_tRegisterNumberForComputeShader = -1;		// �����÷ο츦 �̿��Ͽ� CSSetUnorderedAccessViews�� �迭 �ʱ�ȭ �䳻; ����! MSVC�� �ƴ� �����Ϸ����� ���� �� ��
}

void C_StructuredBuffer::MF_Bind_StructuredBufferForComputingWithUndorederAccessView(UINT _RegisterNumberForComputeShader)
{
	SDK_M_uRegisterNumberForComputeShader = _RegisterNumberForComputeShader;
	UINT i = -1;		// �����÷ο츦 �̿��Ͽ� CSSetUnorderedAccessViews�� �迭 �ʱ�ȭ
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->CSSetUnorderedAccessViews(_RegisterNumberForComputeShader
		, 1, CP_DX_M_UnorderedAccessView.GetAddressOf(), &i);
}

void C_StructuredBuffer::MF_Clear_StructuredBufferForComputingWithUnorderedAccessView()
{
	ID3D11UnorderedAccessView* P_DX_T_UnorderedAccessView = nullptr;
	UINT i = -1;		// �����÷ο츦 �̿��Ͽ� CSSetUnorderedAccessViews�� �迭 �ʱ�ȭ
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->CSSetUnorderedAccessViews(SDK_M_uRegisterNumberForComputeShader, 1, &P_DX_T_UnorderedAccessView, &i);
	SDK_M_uRegisterNumberForComputeShader = -1;		// �����÷ο츦 �̿��Ͽ� CSSetUnorderedAccessViews�� �迭 �ʱ�ȭ �䳻; ����! MSVC�� �ƴ� �����Ϸ����� ���� �� ��
}

void C_StructuredBuffer::MF_Set_StructuredBufferByData(void* _Data, UINT _ElementSize, UINT _ElementCount)
{
	SDK_M_ElementSize = _ElementSize;
	SDK_M_ElementCount = _ElementCount;

	// �б����� ���ۿ��� -> �ý��۸޸𸮷� ����
	//// ������ ���ۿ� ����ü
	D3D11_MAPPED_SUBRESOURCE tSubRes = {};

	//// DeviceContext�� Map()���� GPU�� Lock�� �ɾ� GPU ���� ���� �� CPU�� ������ ����
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->Map(CP_DX_M_StructuredBufferForWriting.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &tSubRes);

	memcpy(tSubRes.pData, _Data, _ElementSize * _ElementCount);     // SDK_M_ElementSize�� SDK_M_ElementCount�� �����ϴ� ���� ���ڷ� �����ϴ� �ͺ��� �� ����(SIMD ����ȭ)

	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->Unmap(CP_DX_M_StructuredBufferForWriting.Get(), 0);

	// �б����� ���ۿ��� �߰� �Ű��� ���۷� ����
	//// CopyResource�� GPU�޸� �������� ��ɾ�; �ƹ��� �����ص�, Dest�� src��ġ�� memcpy�ϰ� �ٸ� �� ���� ���ϼ��� ���µ�, �̷� ������ ����ũ�μ���Ʈ�� �峪�´� ����
	C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->CopyResource(CP_DX_M_StructuredBufferForTransfer.Get(), CP_DX_M_StructuredBufferForWriting.Get());
}
