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

    DS_MaterialConstant                 DS_M_MaterialConstant;                  // DS_MaterialConstant; 상수버퍼에 바인딩해서 쓸 구조체

    UINT                                SDK_M_GroupCountX;                      // UINT; 쉐이더에 할당되는 그룹 수(X-Axis)
    UINT                                SDK_M_GroupCountY;                      // UINT; 쉐이더에 할당되는 그룹 수(Y-Axis)
    UINT                                SDK_M_GroupCountZ;                      // UINT; 쉐이더에 할당되는 그룹 수(Z-Axis)

    UINT                                SDK_M_ThreadPerGroupX;                  // UINT; 그룹X 당, 할당되는 쓰레드 수
    UINT                                SDK_M_ThreadPerGroupY;                  // UINT; 그룹Y 당, 할당되는 쓰레드 수
    UINT                                SDK_M_ThreadPerGroupZ;                  // UINT; 그룹Z 당, 할당되는 쓰레드 수

public:
    // 유의! ID3DBlob같은 COM객체는 게터나 세터를 통한 멤버접근을 잘 하지 않음!
    void MF_Bind_ComputeShader();

    void MF_UnBind_ComputeShader();

public:
    virtual void MF_Calculate_GroupXYZ();

public:
    void MF_Create_ComputeShader(const wstring& _Path, const string& _HLSL_Function);

    void MF_Dispatch();

public:
    // 유의! ID3DBlob같은 COM객체는 게터나 세터를 통한 멤버접근을 잘 하지 않음!

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

