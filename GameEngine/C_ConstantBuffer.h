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
    D3D11_BUFFER_DESC           DX_M_ConstantBufferDesc;            // D3D11_BUFFER_DESC;
    E_CONSTANTBUFFER_TYPE       E_M_ConstantBufferType;             // E_CONSTANTBUFFER_TYPE; 버퍼타입으로 바인드될 레지스터 숫자 대체

public:
    void MF_Create_ConstantBuffer(UINT _ByteWidth, E_CONSTANTBUFFER_TYPE _BufferType);      // UINT(D3D11_BUFFER_DESC.ByteWidth): 버퍼크기, E_CONSTANTBUFFER_TYPE: 버퍼타입

public:
    void MF_Bind_ConstantBuffer();

    void MF_Bind_ConstantBufferToComputeShaderOnly();

public:
    void MF_Set_ConstantBufferByData(void* _DataType, UINT _ByteWidth);                     // void*; void* 자료형은 어떤 것이든 받을 수 있는 만능; 유의! 윈도우의 WPARAM과 LPARAM과 유사! 향후, CPU및 GPU간의 병렬을 Lock하기 위한 것을 감안하여 새로운 설계를 해보는 것을 고려해보자

    E_CONSTANTBUFFER_TYPE MF_Get_ConstantBufferType()
    {
        return E_M_ConstantBufferType;
    }
};

