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
    shared_ptr<C_Texture>               SP_M_AtlasTexture;                        // shared_ptr<C_Texture>; 아틀라스 이미지
    Vector2                             VEC2_M_AtlasTextureSize;                  // Vector2; 스프라이트의 크기

    Vector2                             VEC2_M_TopLeftPoint;                      // Vector2; 유의! 서양식 방향지칭법으로 통일함
    Vector2                             VEC2_M_SpriteSize;                        // Vector2; 스프라이트의 크기
    Vector2                             VEC2_M_SpriteOffset;                      // Vector2; 스프라이트의 간격

public:
    inline shared_ptr<C_Texture> MF_Get_AtlaseTexture()
    {
        return SP_M_AtlasTexture;
    }

    inline Vector2 MF_Get_AtlaseTextureSize()
    {
        return VEC2_M_AtlasTextureSize;
    }

    inline Vector2 MF_Get_TopLeftPoint()
    {
        return VEC2_M_TopLeftPoint;
    }

    inline Vector2 MF_Get_SpriteSize()
    {
        return VEC2_M_SpriteSize;
    }

    inline Vector2 MF_Get_SpriteOffset()
    {
        return VEC2_M_SpriteOffset;
    }

public:
    inline void MF_Set_AtlasTexture(shared_ptr<C_Texture> _SP_AtlasTexture)
    {
        SP_M_AtlasTexture = _SP_AtlasTexture;
    }

    inline void MF_Set_AtlaseTextureSize(Vector2 _VEC2_AtlasTextureSize)
    {
        VEC2_M_AtlasTextureSize = _VEC2_AtlasTextureSize;
    }

    inline void MF_Set_TopLeftPoint(Vector2 _VEC2_TopLeftPoint)
    {
        if (nullptr == SP_M_AtlasTexture)
        {
            VEC2_M_TopLeftPoint = Vector2(0.f, 0.f);
            VEC2_M_AtlasTextureSize = Vector2(0.f, 0.f);
            VEC2_M_SpriteSize = Vector2(0.f, 0.f);
            VEC2_M_SpriteOffset = Vector2(0.f, 0.f);
            return;
        }

        VEC2_M_TopLeftPoint = _VEC2_TopLeftPoint / Vector2(SP_M_AtlasTexture->MF_Get_TextureWidth(), SP_M_AtlasTexture->MF_Get_TextureHeight());
    }

    inline void MF_Set_SpriteSize(Vector2 _VEC2_SpriteSize)
    {
        VEC2_M_SpriteSize = _VEC2_SpriteSize;
    }

    inline void MF_Set_SpriteOffset(Vector2 _VEC2_SpriteOffset)
    {
        VEC2_M_SpriteOffset = _VEC2_SpriteOffset;
    }
};

