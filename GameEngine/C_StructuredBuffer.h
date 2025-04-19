#pragma once
#include "C_Entity.h"
class C_StructuredBuffer :      // ����, CP_DX_M_StructuredBufferForWriting �����ؼ� �ƿ� Ŭ������ �����Ͽ� å�ӿ�Ģ
    public C_Entity
{
public:
    C_StructuredBuffer();

public:
    ~C_StructuredBuffer();

protected:
    ComPtr<ID3D11Buffer>                     CP_DX_M_StructuredBufferForTransfer;        // ComPtr<ID3D11Buffer>; CPU�� GPU�� �߰� �Ű��� ������ ����
    ComPtr<ID3D11Buffer>                     CP_DX_M_StructuredBufferForWriting;         // ComPtr<ID3D11Buffer>; CPU�� ���� ���� ��������� ����
    ComPtr<ID3D11Buffer>                     CP_DX_M_StructuredBufferForReading;         // ComPtr<ID3D11Buffer>; CPU�� �б� ���� ��������� ����

    D3D11_BUFFER_DESC                        DX_M_StructuredBufferDesc;                  // D3D11_BUFFER_DESC
    E_STRUCTUREDBUFFER_TYPE                  E_M_StructuredBuffeType;                    // E_STRUCTUREDBUFFER_TYPE

    ComPtr<ID3D11ShaderResourceView>         CP_DX_M_ShaderResourceView;                 // ComPtr<ID3D11ShaderResourceView>
    ComPtr<ID3D11UnorderedAccessView>        CP_DX_M_UnorderedAccessView;                // ComPtr<ID3D11UnorderedAccessView>

    UINT                                     SDK_M_ElementSize;                          // UINT; ����! ����ȭ ���۴� StructureByteStride�� ����ϹǷ�, �ʼ������� ����ϴ� �����!
    UINT                                     SDK_M_ElementCount;                         // UINT

public:
    void MF_Create_StructuredBuffer(UINT _ElementSize, UINT _ElementCount, E_STRUCTUREDBUFFER_TYPE _StructuredBufferType, void* _Data = nullptr);

public:
    void MF_Bind_StructuredBuffer();

    void MF_Clear_StructuredBuffer();

    void MF_Bind_StructuredBufferForComputingWithShaderResourceView();

    void MF_Clear_StructuredBufferForComputingWithShaderResourceView();

    void MF_Bind_StructuredBufferForComputingWithUndorederAccessView();

    void MF_Clear_StructuredBufferForComputingWithUnorderedAccessView();

public:
    inline void MF_Get_StructuredBufferByData(void* _Data, UINT _ElementSize, UINT _ElementCount)
    {
        if (_ElementSize == 0)
            _ElementSize = SDK_M_ElementSize;

        if (_ElementCount == 0)
            _ElementCount = SDK_M_ElementCount;

        // �߰� �Ű��� ���ۿ��� �б����� ���۷� ����
        //// CopyResource�� GPU�޸� �������� ��ɾ�; �ƹ��� �����ص�, Dest�� src��ġ�� memcpy�ϰ� �ٸ� �� ���� ���ϼ��� ���µ�, �̷� ������ ����ũ�μ���Ʈ�� �峪�´� ����
        C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->CopyResource(CP_DX_M_StructuredBufferForReading.Get(), CP_DX_M_StructuredBufferForTransfer.Get());

        // �б����� ���ۿ��� -> �ý��۸޸𸮷� ����
        //// ������ ���ۿ� ����ü
        D3D11_MAPPED_SUBRESOURCE tSubRes = {};

        //// DeviceContext�� Map()���� GPU�� Lock�� �ɾ� GPU ���� ���� �� CPU�� ������ ����
        C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->Map(CP_DX_M_StructuredBufferForReading.Get(), 0, D3D11_MAP_READ, 0, &tSubRes);

        //// �޸𸮸� ������ �����ϴ� ���� ������
        memcpy(_Data, tSubRes.pData, _ElementSize * _ElementCount);

        //// DeviceContext�� Unmap()���� GPU�� Lock�� Ǯ�� CPU ���� ���� �� GPU�� ������ ����
        C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->Unmap(CP_DX_M_StructuredBufferForReading.Get(), 0);
    }

    inline void MF_Set_StructuredBufferByData(void* _Data, UINT _ElementSize, UINT _ElementCount)
    {
            _ElementSize = SDK_M_ElementSize;
            _ElementCount = SDK_M_ElementCount;

        // �б����� ���ۿ��� -> �ý��۸޸𸮷� ����
        //// ������ ���ۿ� ����ü
        D3D11_MAPPED_SUBRESOURCE tSubRes = {};

        //// DeviceContext�� Map()���� GPU�� Lock�� �ɾ� GPU ���� ���� �� CPU�� ������ ����
        C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->Map(CP_DX_M_StructuredBufferForWriting.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &tSubRes);

        memcpy(tSubRes.pData, _Data, _ElementSize * _ElementCount);

        C_Device::SF_Get_Instance()->MF_Get_DeviceContext()->Unmap(CP_DX_M_StructuredBufferForWriting.Get(), 0);

        // �б����� ���ۿ��� �߰� �Ű��� ���۷� ����
        //// CopyResource�� GPU�޸� �������� ��ɾ�; �ƹ��� �����ص�, Dest�� src��ġ�� memcpy�ϰ� �ٸ� �� ���� ���ϼ��� ���µ�, �̷� ������ ����ũ�μ���Ʈ�� �峪�´� ����
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

