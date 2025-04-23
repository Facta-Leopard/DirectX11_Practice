#pragma once
#include "C_Resource.h"

#include "C_GraphicShader.h"

class C_Material :
    public C_Resource
{
public:
    C_Material();

public:
    ~C_Material();

protected:
    shared_ptr<C_GraphicShader>             SP_M_GraphicShader;                     // shared_ptr<C_GraphicShader>
    shared_ptr<C_Texture>                   SP_M_Texture_s[_TEXTURE_END];           // shared_ptr<C_Texture>
    DS_MaterialConstant                     DS_M_MaterialConstant;                  // DS_MaterialConstant

    // 캐싱용
    static C_ConstantBuffer*                S_P_ConstantBuffer;                     // static C_ConstantBuffer*;

public:
    void MF_Bind_Material();

public:
    inline shared_ptr<C_GraphicShader> MF_Get_GraphicShader()                                           // Getter
    {
        return SP_M_GraphicShader;
    }

    inline shared_ptr<C_Texture> MF_Get_Texture(E_TEXTURE_NUMBER _TextureNumber)                        // Getter
    {
        return SP_M_Texture_s[_TextureNumber];
    }


    inline DS_MaterialConstant MF_Get_MaterialCount()                                                   // Getter
    {
        return DS_M_MaterialConstant;
    }

public:
    inline void MF_Set_GraphicShader(shared_ptr<C_GraphicShader> _SP_GraphicShader)                     // Setter; 유의! C_Texture는 복사 생성자 막아두었으므로, C_Texture를 인자로 받아, shared_ptr로 감싸서 넘기는 것은 move를 써도 불가능함!; 유의! 이걸 회피한다고 && 이동연산자를 만들어서 회피해도, 타 스마트 포인터가 해제시킨 댕글링 문제 터질 수 있음!
    {
        SP_M_GraphicShader = _SP_GraphicShader;
    }

    inline void MF_Set_Texture(shared_ptr<C_Texture> _SP_Texture, E_TEXTURE_NUMBER _TextureNumber)      // Setter; 유의! C_Texture는 복사 생성자 막아두었으므로, C_Texture를 인자로 받아, shared_ptr로 감싸서 넘기는 것은 move를 써도 불가능함!; 유의! 이걸 회피한다고 && 이동연산자를 만들어서 회피해도, 타 스마트 포인터가 해제시킨 댕글링 문제 터질 수 있음!
    {
        SP_M_Texture_s[_TextureNumber] = _SP_Texture;
    }

    inline void MF_Set_MatrialCount(UINT _XM_UINT, int _Index)                                             // Setter; Overload
    {
        DS_M_MaterialConstant.SDK_XM_UINT_Constant_s[_Index] = _XM_UINT;
    }

    inline void MF_Set_MatrialCount(FLOAT _XM_FLOAT, int _Index)                                           // Setter; Overload
    {
        DS_M_MaterialConstant.SDK_XM_FLOAT_Constant_s[_Index] = _XM_FLOAT;
    }

    inline void MF_Set_MatrialCount(XMFLOAT2 _XM_FLOAT2, int _Index)                                         // Setter; Overload
    {
        DS_M_MaterialConstant.SDK_XM_FLOAT2_Constant_s[_Index] = _XM_FLOAT2;
    }

    inline void MF_Set_MatrialCount(XMFLOAT4 _XM_FLOAT4, int _Index)                                         // Setter; Overload
    {
        DS_M_MaterialConstant.SDK_XM_FLOAT4_Constant_s[_Index] = _XM_FLOAT4;
    }

    inline void MF_Set_MatrialCount(XMFLOAT4X4 _XM_FLOATX4, int _Index)                                          // Setter; Overload
    {
        DS_M_MaterialConstant.SDK_XM_FLOAT4X4_Constant_s[_Index] = _XM_FLOATX4;
    }

    inline void MF_Set_MatrialCount(BOOL _XM_BOOL, E_TEXTURE_NUMBER _E_TextureNumver)                 // Setter; Overload
    {
        DS_M_MaterialConstant.SDK_XM_BOOL_Texture_s[_E_TextureNumver] = _XM_BOOL;
    }



};

