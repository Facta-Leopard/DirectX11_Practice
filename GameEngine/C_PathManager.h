#pragma once
#include "C_Singleton.h"

#include"define.h"

class C_PathManager :
    public C_Singleton< C_PathManager>
{
    SINGLE(C_PathManager);

protected:
    wchar_t     M_ProjectPath_s[255];                     // Project Directory Address
    wchar_t     M_SolutionPath_s[255];                    // Solution Directory Address
    wchar_t     M_ResourcePath_s[255];                    // Resource Directory Address
    wchar_t     M_SaveAndLoadPath_s[255];                 // 향후, 정리 필요; Save And Load Directory Address

public:
    void MF_Initialize();


    // 유의: 배열을 버퍼로 읽을 때는 포인터로 하여야 함!
    // 배열은 포인터로 표현이 가능!
    inline wchar_t* MF_GetProjectPath_s()                         // Getter; M_ProjectPath_s
    {
        return M_ProjectPath_s;
    }

    inline wchar_t* MF_GetSolutionPath_s()                        // Getter; M_SolutionPath_s
    {
        return M_SolutionPath_s;
    }

    inline wchar_t* MF_GetResourcePath_s()                        // Getter; M_ResourcePath_s
    {
        return M_ResourcePath_s;
    }

    inline wchar_t* MF_GetSaveAndLoadPath_s()                     // Getter; M_SaveAndLoadPath_s
    {
        return M_SaveAndLoadPath_s;
    }
};

