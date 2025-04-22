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

    // Ä³½Ì¿ë
    static C_ConstantBuffer*                S_P_ConstantBuffer;                     // static C_ConstantBuffer*;

public:
    void MF_Bind_Material();

public:
    inline shared_ptr<C_GraphicShader> MF_Get_GraphicShader()                                           // Getter
    {
        return SP_M_GraphicShader;
    }

    inline void MF_Set_GraphicShader(shared_ptr<C_GraphicShader> _SP_GraphicShader)                     // Setter; Overload
    {
        SP_M_GraphicShader = _SP_GraphicShader;
    }

    //inline void MF_Set_GraphicShader(C_GraphicShader _GraphicShader)                                    // Setter; Overload
    //{
    //    SP_M_GraphicShader = make_shared<C_GraphicShader>(move(_GraphicShader));
    //}

    inline shared_ptr<C_Texture> MF_Get_Texture(E_TEXTURE_NUMBER _TextureNumber)                        // Getter
    {
        return SP_M_Texture_s[_TextureNumber];
    }

    inline void MF_Set_Texture(shared_ptr<C_Texture> _SP_Texture, E_TEXTURE_NUMBER _TextureNumber)      // Setter; Overload
    {
        SP_M_Texture_s[_TextureNumber] = _SP_Texture;
    }

    //inline void MF_Set_Texture(C_Texture _Texture, E_TEXTURE_NUMBER _TextureNumber)                     // Setter; Overload
    //{
    //    SP_M_Texture_s[_TextureNumber] = make_shared<C_Texture>(move(_Texture));
    //}

    inline DS_MaterialConstant MF_Get_MaterialCount()                                                   // Getter
    {
        return DS_M_MaterialConstant;
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

