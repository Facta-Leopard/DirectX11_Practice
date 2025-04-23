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
    inline void MF_Set_Texture(shared_ptr<C_Texture> _SP_Texture)           // Setter; 유의! C_Texture는 복사 생성자 막아두었으므로, C_Texture를 인자로 받아, shared_ptr로 감싸서 넘기는 것은 move를 써도 불가능함!; 유의! 이걸 회피한다고 && 이동연산자를 만들어서 회피해도, 타 스마트 포인터가 해제시킨 댕글링 문제 터질 수 있음!
    {
        SP_M_Texture = _SP_Texture;
    }

    inline void MF_Set_Color(Vector4 _VEC4_Color)
    {
        VEC4_M_Color = _VEC4_Color;
    }


};

