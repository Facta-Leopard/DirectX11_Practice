#pragma once
#include "C_Resource.h"

class C_ComputeShader :
    public C_Resource
{
public:
    C_ComputeShader();

public:
    ~C_ComputeShader();

protected:
    ComPtr<ID3DBlob> CP_DX_M_ErrorBlob;

public:
    // ����! ID3DBlob���� COM��ü�� ���ͳ� ���͸� ���� ��������� �� ���� ����!
};

