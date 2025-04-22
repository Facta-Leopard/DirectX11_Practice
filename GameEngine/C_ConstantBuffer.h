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
    ComPtr<ID3D11Buffer>        CP_DX_M_ConstantBuffer;             // ComPtr<ID3D11Buffer>; ����
    D3D11_BUFFER_DESC           DX_M_ConstantBufferDesc;            // D3D11_BUFFER_DESC; ������۴� .StructureByteStride�� �� ���� �����Ƿ� ����ȭ������ ����� SDK_M_ElementSize�� ���� ����
    E_CONSTANTBUFFER_TYPE       E_M_ConstantBufferType;             // E_CONSTANTBUFFER_TYPE; ����Ÿ������ ���ε�� �������� ���� ��ü

public:
    void MF_Create_ConstantBuffer(UINT _ElementSize, UINT _ElementCount, E_CONSTANTBUFFER_TYPE _BufferType);      // UINT(D3D11_BUFFER_DESC.ByteWidth): Overload and Wrapping; ����ũ��, E_CONSTANTBUFFER_TYPE: ����Ÿ��

    void MF_Create_ConstantBuffer(UINT _ByteWidth, E_CONSTANTBUFFER_TYPE _BufferType);                                    // UINT(D3D11_BUFFER_DESC.ByteWidth): Overload; ����ũ��, E_CONSTANTBUFFER_TYPE: ����Ÿ��

public:
    void MF_Bind_ConstantBuffer();

    void MF_Bind_ConstantBufferToComputeShaderOnly();

public:
    inline void MF_Set_ConstantBufferByData(void* _DataType, UINT _ElementSize, UINT _ElementCount)                      // void*; Overload and Wrapping; void* �ڷ����� � ���̵� ���� �� �ִ� ����; ����! �������� WPARAM�� LPARAM�� ����! ����, CPU�� GPU���� ������ Lock�ϱ� ���� ���� �����Ͽ� ���ο� ���踦 �غ��� ���� ����غ���
    {
        MF_Set_ConstantBufferByData(_DataType, (UINT)(_ElementSize * _ElementCount));
    }

    void MF_Set_ConstantBufferByData(void* _DataType, UINT _ByteWidth);                                                    // void*; Overload; void* �ڷ����� � ���̵� ���� �� �ִ� ����; ����! �������� WPARAM�� LPARAM�� ����! ����, CPU�� GPU���� ������ Lock�ϱ� ���� ���� �����Ͽ� ���ο� ���踦 �غ��� ���� ����غ���
    // ����! ������۴� GPU�� ���� �۾��� �� ������ ���� ������, MF_Clear()���� ������ �� �ʿ䰡 ����!

    inline E_CONSTANTBUFFER_TYPE MF_Get_ConstantBufferType()
    {
        return E_M_ConstantBufferType;
    }
};