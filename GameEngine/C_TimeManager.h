#pragma once
#include "C_Singleton.h"
class C_TimeManager :
    public C_Singleton<C_TimeManager>
{
    SINGLE(C_TimeManager);

};

