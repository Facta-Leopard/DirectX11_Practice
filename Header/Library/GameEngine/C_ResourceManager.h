#pragma once
#include "C_Singleton.h"
class C_ResourceManager :
    public C_Singleton<C_ResourceManager>
{
    SINGLE(C_ResourceManager)

public:
    HRESULT MF_Initialize();
};

