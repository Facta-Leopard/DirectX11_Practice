#pragma once
#include "C_Singleton.h"
#include "global.h"

class C_DebugManager :
    public C_Singleton<C_DebugManager>
{
    SINGLE(C_DebugManager)

private:
    bool            M_IsDebugSrcreen;                   // bool

    //향후, Object관련 생성 예정

public:
    HRESULT MF_Initialize();

    void MF_Update();

    void MF_DebugRender();

public:
    inline bool MF_Get_DebugScreenOn()                   // Getter; M_IsDebugSrcreenOn
    {
        return M_IsDebugSrcreen;
    }

public:
    inline void MF_Set_ScreenOn()                        // Setter; M_IsDebugSrcreenOn
    {
        M_IsDebugSrcreen = true;
    }

    inline void MF_Set_ScreenOff()                       // Setter; M_IsDebugSrcreenOn
    {
        M_IsDebugSrcreen = false;
    }

public:

};

