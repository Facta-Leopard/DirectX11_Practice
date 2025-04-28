#pragma once
#include "C_Resource.h"

class C_Sprite;

class C_FlipBook :
    public C_Resource
{
public:
    C_FlipBook();

public:
    ~C_FlipBook();

protected:
    vector<shared_ptr<C_Sprite>>            STL_SP_M_Sprite;            // vector<shared_ptr<C_Sprite>>

public:
    inline int MF_Get_SpriteSize()
    {
        return (int)STL_SP_M_Sprite.size();
    }

    inline shared_ptr<C_Sprite> MF_Get_Sprite(int _Index)
    {
        return STL_SP_M_Sprite[_Index];
    }

    inline void MF_Attach_Sprite(shared_ptr<C_Sprite> _SP_Sprite) { STL_SP_M_Sprite.push_back(_SP_Sprite); }

};