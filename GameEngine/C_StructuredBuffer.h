#pragma once
#include "C_Entity.h"
class C_StructuredBuffer :      // 향후, CP_DX_M_StructuredBufferForWriting 관련해서 아예 클래스를 구분하여 SOLID에 따라 재구성하는 것을 고려해보자
    public C_Entity
{
public:
    C_StructuredBuffer();

public:
    ~C_StructuredBuffer();

protected:
    ComPtr<ID3D11Buffer>                     CP_DX_M_StructuredBufferForTransfer;        // ComPtr<ID3D11Buffer>; CPU와 GPU의 중간 매개자 역할의 버퍼
    ComPtr<ID3D11Buffer>                     CP_DX_M_StructuredBufferForWriting;         // ComPtr<ID3D11Buffer>; CPU가 쓰기 위한 전용목적의 버퍼
    ComPtr<ID3D11Buffer>                     CP_DX_M_StructuredBufferForReading;         // ComPtr<ID3D11Buffer>; CPU가 읽기 위한 전용목적의 버퍼

    D3D11_BUFFER_DESC                        DX_M_StructuredBufferDesc;                  // D3D11_BUFFER_DESC
    E_STRUCTUREDBUFFER_TYPE                  E_M_StructuredBuffeType;                    // E_STRUCTUREDBUFFER_TYPE

    ComPtr<ID3D11ShaderResourceView>         CP_DX_M_ShaderResourceView;                 // ComPtr<ID3D11ShaderResourceView>
    ComPtr<ID3D11UnorderedAccessView>        CP_DX_M_UnorderedAccessView;                // ComPtr<ID3D11UnorderedAccessView>

    UINT                                     SDK_M_ElementSize;                          // UINT; 유의! 구조화 버퍼는 StructureByteStride를 써야하므로, 필수적으로 써야하는 요소임!
    UINT                                     SDK_M_ElementCount;                         // UINT

    UINT                                     SDK_M_tRegisterNumberForComputeShader;      // UINT; Compute Shader에 쓰인 ShaderResourceView로 세팅된 데 쓰여 다시금 사용되는 멤버로 쓰임
    UINT                                     SDK_M_uRegisterNumberForComputeShader;      // UINT; Compute Shader에 쓰인 UnorderedAccessView로 세팅된 데 쓰여 다시금 사용되는 멤버로 쓰임

public:
    void MF_Create_StructuredBuffer(UINT _ElementSize, UINT _ElementCount, E_STRUCTUREDBUFFER_TYPE _StructuredBufferType, void* _Data = nullptr);

public:
    void MF_Bind_StructuredBuffer(UINT _RegisterNumber);                                                        // 그래픽 파이프라인에 바인딩은 매 프레임당 하는 형식

    void MF_Clear_StructuredBuffer(UINT _RegisterNumber);                                                       // 그래픽 파이프라인에 바인딩된 것을 해제

    void MF_Bind_StructuredBufferForComputingWithShaderResourceView(UINT _RegisterNumberForComputeShader);      // 한 프레임에 컴퓨트 쉐이더에 따라 여러번 호출하므로, 다시금 호출 안하도록 최근 사용된 레지스터 넘버를 기록하는 게 좋음

    void MF_Clear_StructuredBufferForComputingWithShaderResourceView();                                         // 컴퓨트 쉐이더에 썻던 레지스터 넘버를 이용해서 쉐이더 설정 해제

    void MF_Bind_StructuredBufferForComputingWithUndorederAccessView(UINT _RegisterNumberForComputeShader);     // 한 프레임에 컴퓨트 쉐이더에 따라 여러번 호출하므로, 다시금 호출 안하도록 최근 사용된 레지스터 넘버를 기록하는 게 좋음

    void MF_Clear_StructuredBufferForComputingWithUnorderedAccessView();                                        // 컴퓨트 쉐이더에 썻던 레지스터 넘버를 이용해서 쉐이더 설정 해제

public:
    inline void MF_Get_StructuredBufferByData(void* _Data, UINT _ElementSize, UINT _ElementCount)
    {
        if (_ElementSize == 0)
            _ElementSize = SDK_M_ElementSize;

        if (_ElementCount == 0)
            _ElementCount = SDK_M_ElementCount;

        // 중간 매개의 버퍼에서 읽기전용 버퍼로 복사
        //// CopyResource는 GPU메모리 복사전용 명령어; 아무리 생각해도, Dest랑 src위치가 memcpy하고 다른 걸 보면 통일성이 없는데, 이런 점에서 마이크로소프트는 욕나온다 씨발
        C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->CopyResource(CP_DX_M_StructuredBufferForReading.Get(), CP_DX_M_StructuredBufferForTransfer.Get());

        // 읽기전용 버퍼에서 -> 시스템메모리로 복사
        //// 데이터 전송용 구조체
        D3D11_MAPPED_SUBRESOURCE tSubRes = {};

        //// DeviceContext의 Map()으로 GPU에 Lock을 걸어 GPU 접근 방지 및 CPU가 데이터 접근
        C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->Map(CP_DX_M_StructuredBufferForReading.Get(), 0, D3D11_MAP_READ, 0, &tSubRes);

        //// 메모리를 통으로 복사하는 빠른 복사방법
        memcpy(_Data, tSubRes.pData, _ElementSize * _ElementCount);

        //// DeviceContext의 Unmap()으로 GPU에 Lock을 풀어 CPU 접근 방지 및 GPU가 데이터 접근
        C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->Unmap(CP_DX_M_StructuredBufferForReading.Get(), 0);
    }

    inline void MF_Set_StructuredBufferByData(void* _Data, UINT _ElementSize, UINT _ElementCount)
    {
        SDK_M_ElementSize = _ElementSize;
        SDK_M_ElementCount = _ElementCount;

        // 읽기전용 버퍼에서 -> 시스템메모리로 복사
        //// 데이터 전송용 구조체
        D3D11_MAPPED_SUBRESOURCE tSubRes = {};

        //// DeviceContext의 Map()으로 GPU에 Lock을 걸어 GPU 접근 방지 및 CPU가 데이터 접근
        C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->Map(CP_DX_M_StructuredBufferForWriting.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &tSubRes);

        memcpy(tSubRes.pData, _Data, _ElementSize * _ElementCount);     // SDK_M_ElementSize나 SDK_M_ElementCount로 접근하는 것이 인자로 접근하는 것보다 더 느림(SIMD 최적화)

        C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->Unmap(CP_DX_M_StructuredBufferForWriting.Get(), 0);

        // 읽기전용 버퍼에서 중간 매개의 버퍼로 복사
        //// CopyResource는 GPU메모리 복사전용 명령어; 아무리 생각해도, Dest랑 src위치가 memcpy하고 다른 걸 보면 통일성이 없는데, 이런 점에서 마이크로소프트는 욕나온다 씨발
        C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->CopyResource(CP_DX_M_StructuredBufferForTransfer.Get(), CP_DX_M_StructuredBufferForWriting.Get());
    }

    inline UINT MF_Get_ElementSize()
    {
        return SDK_M_ElementSize;
    }

    inline void MF_Set_ElementSize(UINT _SDK_ElementSize)
    {
        SDK_M_ElementSize = _SDK_ElementSize;
    }

    inline UINT MF_Get_ElementCount()
    {
        return SDK_M_ElementCount;
    }

    inline void MF_Set_ElementCount(UINT _SDK_ElementCount)
    {
        SDK_M_ElementCount = _SDK_ElementCount;
    }
};

