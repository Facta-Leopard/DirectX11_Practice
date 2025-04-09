#pragma once
#include "C_Singleton.h"

class C_CollisionManager :
    public C_Singleton<C_CollisionManager>
{
    SINGLE(C_CollisionManager)

protected:


public:
    HRESULT MF_Initialize();

    void MF_Update();



};

