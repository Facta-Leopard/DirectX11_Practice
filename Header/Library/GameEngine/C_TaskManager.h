#pragma once
#include "C_Singleton.h"

#include "global.h"

class C_TaskManager :
    public C_Singleton<C_TaskManager>
{
    SINGLE(C_TaskManager)

public:
    HRESULT MF_Initialize();

    void MF_Update();
};

