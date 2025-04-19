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
        MF_Set_ConstantBufferByData(_DataType, (UINT)(_ElementSize* _ElementCount));
    }

    inline void MF_Set_ConstantBufferByData(void* _DataType, UINT _ByteWidth)                                                    // void*; Overload; void* �ڷ����� � ���̵� ���� �� �ִ� ����; ����! �������� WPARAM�� LPARAM�� ����! ����, CPU�� GPU���� ������ Lock�ϱ� ���� ���� �����Ͽ� ���ο� ���踦 �غ��� ���� ����غ���
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

    inline E_CONSTANTBUFFER_TYPE MF_Get_ConstantBufferType()
    {
        return E_M_ConstantBufferType;
    }

    // ����! ������۴� GPU�� ���� �۾��� �� ������ ���� ������, MF_Clear()���� ������ �� �ʿ䰡 ����!
};

