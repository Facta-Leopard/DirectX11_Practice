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
    // 유의! ID3DBlob같은 COM객체는 게터나 세터를 통한 멤버접근을 잘 하지 않음!
};

