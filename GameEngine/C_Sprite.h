#pragma once
#include "C_Resource.h"
class C_Sprite :
    public C_Resource
{
public:
    C_Sprite();

public:
    C_Sprite(const C_Sprite& _Origin) = delete;
    

public:
    ~C_Sprite();

protected:
    shared_ptr<C_Texture>                SP_M_AtlasTexture;                        // shared_ptr<C_Texture>; 아틀라스 이미지
    XMVECTOR                             XM_VEC2_M_AtlasTextureSize;                  // XMVECTOR; 스프라이트의 크기

    XMVECTOR                             XM_VEC2_M_TopLeftPoint;                      // XMVECTOR; 유의! 서양식 방향지칭법으로 통일함
    XMVECTOR                             XM_VEC2_M_SpriteSize;                        // XMVECTOR; 스프라이트의 크기
    XMVECTOR                             XM_VEC2_M_SpriteOffset;                      // XMVECTOR; 스프라이트의 간격

public:
    inline shared_ptr<C_Texture> MF_Get_AtlaseTexture()
    {
        return SP_M_AtlasTexture;
    }

    inline XMVECTOR MF_Get_AtlaseTextureSize()
    {
        return XM_VEC2_M_AtlasTextureSize;
    }

    inline XMVECTOR MF_Get_TopLeftPoint()
    {
        return XM_VEC2_M_TopLeftPoint;
    }

    inline XMVECTOR MF_Get_SpriteSize()
    {
        return XM_VEC2_M_SpriteSize;
    }

    inline XMVECTOR MF_Get_SpriteOffset()
    {
        return XM_VEC2_M_SpriteOffset;
    }

public:
    inline void MF_Set_AtlasTexture(shared_ptr<C_Texture> _SP_AtlasTexture)
    {
        SP_M_AtlasTexture = _SP_AtlasTexture;
    }

    inline void MF_Set_AtlaseTextureSize(XMVECTOR _XM_VEC2_AtlasTextureSize)
    {
        XM_VEC2_M_AtlasTextureSize = _XM_VEC2_AtlasTextureSize;
    }

    inline void MF_Set_TopLeftPoint(XMVECTOR _XM_VEC2_TopLeftPoint)
    {
        if (nullptr == SP_M_AtlasTexture)
        {
            XM_VEC2_M_TopLeftPoint     = XMVectorSet(0.f, 0.f, 0.f, 0.f);
            XM_VEC2_M_AtlasTextureSize = XMVectorSet(0.f, 0.f, 0.f, 0.f);
            XM_VEC2_M_SpriteSize       = XMVectorSet(0.f, 0.f, 0.f, 0.f);
            XM_VEC2_M_SpriteOffset     = XMVectorSet(0.f, 0.f, 0.f, 0.f);
            return;
        }

        XM_VEC2_M_TopLeftPoint = _XM_VEC2_TopLeftPoint / XMVectorSet((float)SP_M_AtlasTexture->MF_Get_TextureWidth(), (float)SP_M_AtlasTexture->MF_Get_TextureHeight(), 0.f, 0.f);
    }

    inline void MF_Set_SpriteSize(XMVECTOR _XM_VEC2_SpriteSize)
    {
        XM_VEC2_M_SpriteSize = _XM_VEC2_SpriteSize;
    }

    inline void MF_Set_SpriteOffset(XMVECTOR _XM_VEC2_SpriteOffset)
    {
        XM_VEC2_M_SpriteOffset = _XM_VEC2_SpriteOffset;
    }
};

