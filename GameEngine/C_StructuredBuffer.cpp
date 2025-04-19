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

	SDK_M_ElementSize = _ElementSize;
	SDK_M_ElementCount = _ElementCount;

	// GPU 메모리크기 통일; 유의! GPU는 메모리 관리단위가 16 배수이므로 맞춰줘야 함!
	if (0 != ((SDK_M_ElementSize * SDK_M_ElementCount) % 16))
	{
		POPUP(L"0 != ((SDK_M_ElementSize * SDK_M_ElementCount) % 16)", L"in C_StructuredBuffer::MF_Create_StructuredBuffer, 0 != ((SDK_M_ElementSize * SDK_M_ElementCount) % 16)")
	}

	// 버퍼 전체 용량
	DX_M_StructuredBufferDesc.ByteWidth = SDK_M_ElementSize * SDK_M_ElementCount;

	// 메인 버퍼는 SystemMem 랑 통신 불가능
	DX_M_StructuredBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	DX_M_StructuredBufferDesc.CPUAccessFlags = 0;

	// 데이터 요소 크기(간격)
	DX_M_StructuredBufferDesc.StructureByteStride = SDK_M_ElementSize;

	// 구조화버퍼 전용 플래그
	DX_M_StructuredBufferDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;

	// 용도
	switch (_StructuredBufferType)
	{
	case _STRUCTUREDBUFFER_SHADERRESOURCEVIEW_ONLY:
		DX_M_StructuredBufferDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		break;
	case _STRUCTUREDBUFFER_UNORDEREDACCESSVIEW_ADDED:
		DX_M_StructuredBufferDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
		break;
	}

	// 메인 버퍼 생성
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

	switch (_StructuredBufferType)		// 유의! 뷰 생성은 무조건 버퍼 생성 후에 되어야 하므로, 위의 스위치문과 합칠 수 없음!; 향후, 분기문 예측에 좋은 방법이 없을지 고민해보자
	{
	case _STRUCTUREDBUFFER_UNORDEREDACCESSVIEW_ADDED:
		// u 레지스터 바인딩전용으로 쓸 UnorderedAccessView 생성
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

	// t 레지스터 바인딩용, ShaderResourceView 생성
	D3D11_SHADER_RESOURCE_VIEW_DESC DX_T_ShaderResourceViewDesc = {};

	DX_T_ShaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
	DX_T_ShaderResourceViewDesc.Buffer.NumElements = _ElementCount;

	if (FAILED(C_Device::SF_Get_Instance()->MF_Get_Device()->CreateShaderResourceView(CP_DX_M_StructuredBufferForTransfer.Get(), &DX_T_ShaderResourceViewDesc, CP_DX_M_ShaderResourceView.GetAddressOf())))
	{
		POPUP_DEBUG(L"CreateShaderResourceView() Failed", L"in C_StructuredBuffer::MF_Create_StructuredBuffer(), CreateShaderResourceView() Failed")
	}

	// UAV 추가 생성

	switch (_StructuredBufferType)
	{
	case _STRUCTUREDBUFFER_UNORDEREDACCESSVIEW_ADDED:
		D3D11_BUFFER_DESC tWriteBufferDesc = {};
		tWriteBufferDesc.ByteWidth = SDK_M_ElementSize * SDK_M_ElementCount;
		tWriteBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		tWriteBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		tWriteBufferDesc.StructureByteStride = SDK_M_ElementSize;
		tWriteBufferDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		tWriteBufferDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

		SDK_T_HResult = C_Device::SF_Get_Instance()->MF_Get_Device()->CreateBuffer(&tWriteBufferDesc, nullptr, CP_DX_M_StructuredBufferForWriting.GetAddressOf());


		D3D11_BUFFER_DESC tReadBufferDesc = {};
		tReadBufferDesc.ByteWidth = SDK_M_ElementSize * SDK_M_ElementCount;
		tReadBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		tReadBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
		tReadBufferDesc.StructureByteStride = SDK_M_ElementSize;
		tReadBufferDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		tReadBufferDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

		SDK_T_HResult = C_Device::SF_Get_Instance()->MF_Get_Device()->CreateBuffer(&tReadBufferDesc, nullptr, CP_DX_M_StructuredBufferForReading.GetAddressOf());
		break;
	}
}

void C_StructuredBuffer::MF_Bind_StructuredBuffer()
{
}

void C_StructuredBuffer::MF_Clear_StructuredBuffer()
{
}

void C_StructuredBuffer::MF_Bind_StructuredBufferForComputingWithShaderResourceView()
{
}

void C_StructuredBuffer::MF_Clear_StructuredBufferForComputingWithShaderResourceView()
{
}

void C_StructuredBuffer::MF_Bind_StructuredBufferForComputingWithUndorederAccessView()
{
}

void C_StructuredBuffer::MF_Clear_StructuredBufferForComputingWithUnorderedAccessView()
{
}
