#pragma once
#include "C_ComputeShader.h"
class C_ColorCompute :
    public C_ComputeShader
{
public:
    C_ColorCompute();

public:
    ~C_ColorCompute();

protected:
    shared_ptr<C_Texture>               SP_M_Texture;                   // shared_ptr<C_Texture>
    Vector4                             VEC4_M_Color;                   // Vector4

public:
    void MF_Bind_ColorCompute();

    void MF_UnBind_ColorCompute();

public:
    virtual void MF_Calculate_GroupXYZ() override;

public:
    inline shared_ptr<C_Texture> MF_Get_Texture()
    {
        return SP_M_Texture;
    }

    inline Vector4 MF_Get_Color()
    {
        return VEC4_M_Color;
    }

public:
    inline void MF_Set_Texture(shared_ptr<C_Texture> _SP_Texture)           // Setter; ����! C_Texture�� ���� ������ ���Ƶξ����Ƿ�, C_Texture�� ���ڷ� �޾�, shared_ptr�� ���μ� �ѱ�� ���� move�� �ᵵ �Ұ�����!; ����! �̰� ȸ���Ѵٰ� && �̵������ڸ� ���� ȸ���ص�, Ÿ ����Ʈ �����Ͱ� ������Ų ��۸� ���� ���� �� ����!
    {
        SP_M_Texture = _SP_Texture;
    }

    inline void MF_Set_Color(Vector4 _VEC4_Color)
    {
        VEC4_M_Color = _VEC4_Color;
    }


};

