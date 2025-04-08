#pragma once
#include "C_Singleton.h"
#include "define.h"

class C_DebugManager :
    public C_Singleton<C_DebugManager>
{
    SINGLE(C_DebugManager)

protected:
    bool            M_IsDebugSrcreen;                   // bool

    //향후, Object관련 생성 예정

public:
    void MF_Initialize();

    void MF_Update();


    inline bool MF_Get_DebugScreenOn()                   // Getter; M_IsDebugSrcreenOn
    {
        return M_IsDebugSrcreen;
    }

    inline void MF_Set_ScreenOn()                        // Setter; M_IsDebugSrcreenOn
    {
        M_IsDebugSrcreen = true;
    }

    inline void MF_Set_ScreenOff()                       // Setter; M_IsDebugSrcreenOn
    {
        M_IsDebugSrcreen = false;
    }


    void MF_DebugRender();
};

