#pragma once
#include "C_Entity.h"

class C_ConstantBuffer :
    public C_Entity
{
public:
    C_ConstantBuffer();

public:
    ~C_ConstantBuffer();

protected:
    ComPtr<ID3D11Buffer>        CP_DX_M_ConstantBuffer;             // ComPtr<ID3D11Buffer>; 버퍼
    D3D11_BUFFER_DESC           DX_M_ConstantBufferDesc;            // D3D11_BUFFER_DESC; 상수버퍼는 .StructureByteStride을 쓸 일이 없으므로 구조화버퍼의 요소인 SDK_M_ElementSize를 쓰지 않음
    E_CONSTANTBUFFER_TYPE       E_M_ConstantBufferType;             // E_CONSTANTBUFFER_TYPE; 버퍼타입으로 바인드될 레지스터 숫자 대체

public:
    void MF_Create_ConstantBuffer(UINT _ElementSize, UINT _ElementCount, E_CONSTANTBUFFER_TYPE _BufferType);      // UINT(D3D11_BUFFER_DESC.ByteWidth): Overload and Wrapping; 버퍼크기, E_CONSTANTBUFFER_TYPE: 버퍼타입

    void MF_Create_ConstantBuffer(UINT _ByteWidth, E_CONSTANTBUFFER_TYPE _BufferType);                                    // UINT(D3D11_BUFFER_DESC.ByteWidth): Overload; 버퍼크기, E_CONSTANTBUFFER_TYPE: 버퍼타입

public:
    void MF_Bind_ConstantBuffer();

    void MF_Bind_ConstantBufferToComputeShaderOnly();

public:
    inline void MF_Set_ConstantBufferByData(void* _DataType, UINT _ElementSize, UINT _ElementCount)                      // void*; Overload and Wrapping; void* 자료형은 어떤 것이든 받을 수 있는 만능; 유의! 윈도우의 WPARAM과 LPARAM과 유사! 향후, CPU및 GPU간의 병렬을 Lock하기 위한 것을 감안하여 새로운 설계를 해보는 것을 고려해보자
    {
        MF_Set_ConstantBufferByData(_DataType, (UINT)(_ElementSize * _ElementCount));
    }

    void MF_Set_ConstantBufferByData(void* _DataType, UINT _ByteWidth);                                                    // void*; Overload; void* 자료형은 어떤 것이든 받을 수 있는 만능; 유의! 윈도우의 WPARAM과 LPARAM과 유사! 향후, CPU및 GPU간의 병렬을 Lock하기 위한 것을 감안하여 새로운 설계를 해보는 것을 고려해보자
    // 유의! 상수버퍼는 GPU가 쓰기 작업을 할 이유가 없기 때문에, MF_Clear()같은 구성을 할 필요가 없다!

    inline E_CONSTANTBUFFER_TYPE MF_Get_ConstantBufferType()
    {
        return E_M_ConstantBufferType;
    }
};