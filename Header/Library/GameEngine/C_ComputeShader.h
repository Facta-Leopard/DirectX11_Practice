#pragma once
#include "C_Resource.h"

class C_ComputeShader :
    public C_Resource
{
public:
    C_ComputeShader();

    C_ComputeShader(const wstring& _Path, const string& _HLSL_Function
        , UINT _SDK_RegisterGroupX, UINT _SDK_RegisterGroupY, UINT _SDK_RegisterGroupZ);

public:
    ~C_ComputeShader();

protected:
    ComPtr<ID3DBlob>                    CP_DX_M_ErrorBlob;                      // ComPtr<ID3DBlob>

    ComPtr<ID3D11ComputeShader>         CP_DX_M_ComputeShader;                  // ComPtr<ID3D11ComputeShader>
    ComPtr<ID3DBlob>                    CP_DX_M_ComputeShaderBlob;              // ComPtr<ID3DBlob>

    DS_MaterialConstant                 DS_M_MaterialConstant;                  // DS_MaterialConstant; ������ۿ� ���ε��ؼ� �� ����ü

    UINT                                SDK_M_GroupCountX;                      // UINT; ���̴��� �Ҵ�Ǵ� �׷� ��(X-Axis)
    UINT                                SDK_M_GroupCountY;                      // UINT; ���̴��� �Ҵ�Ǵ� �׷� ��(Y-Axis)
    UINT                                SDK_M_GroupCountZ;                      // UINT; ���̴��� �Ҵ�Ǵ� �׷� ��(Z-Axis)

    UINT                                SDK_M_ThreadPerGroupX;                  // UINT; �׷�X ��, �Ҵ�Ǵ� ������ ��
    UINT                                SDK_M_ThreadPerGroupY;                  // UINT; �׷�Y ��, �Ҵ�Ǵ� ������ ��
    UINT                                SDK_M_ThreadPerGroupZ;                  // UINT; �׷�Z ��, �Ҵ�Ǵ� ������ ��

public:
    // ����! ID3DBlob���� COM��ü�� ���ͳ� ���͸� ���� ��������� �� ���� ����!
    void MF_Bind_ComputeShader();

    void MF_UnBind_ComputeShader();

public:
    virtual void MF_Calculate_GroupXYZ();

public:
    void MF_Create_ComputeShader(const wstring& _Path, const string& _HLSL_Function);

    void MF_Dispatch();

public:
    // ����! ID3DBlob���� COM��ü�� ���ͳ� ���͸� ���� ��������� �� ���� ����!

    ComPtr<ID3D11ComputeShader> MF_Get_ComputeShader()
    {
        return  CP_DX_M_ComputeShader;
    }

    DS_MaterialConstant MF_Get_MaterialConstant()
    {
        return DS_M_MaterialConstant;
    }

    UINT MF_Get_GroupCountX()
    {
        return SDK_M_GroupCountX;
    }

    UINT MF_Get_GroupCountY()
    {
        return SDK_M_GroupCountY;
    }

    UINT MF_Get_GroupCountZ()
    {
        return SDK_M_GroupCountZ;
    }

public:

};

