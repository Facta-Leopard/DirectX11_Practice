#pragma once
#include "C_Singleton.h"
class C_PathManager :
    public C_Singleton< C_PathManager>
{
    SINGLE(C_PathManager);

protected:
    wchar_t     M_ProjectPath[255];                     // Project Directory Address
    wchar_t     M_SolutionPath[255];                    // Solution Directory Address
    wchar_t     M_ResourcePath[255];                    // Resource Directory Address
    wchar_t     M_SaveAndLoadPath[255];                 // 향후, 정리 필요; Save And Load Directory Address

public:
    void MF_Initialize();


    // 유의: 배열을 버퍼로 읽을 때는 포인터로 하여야 함!
    // 배열은 포인터로 표현이 가능!
    inline wchar_t* MF_GetProjectPath()                         // Getter; M_ProjectPath
    {
        return M_ProjectPath;
    }

    inline wchar_t* MF_GetSolutionPath()                        // Getter; M_SolutionPath
    {
        return M_SolutionPath;
    }

    inline wchar_t* MF_GetResourcePath()                        // Getter; M_ResourcePath
    {
        return M_ResourcePath;
    }

    inline wchar_t* MF_GetSaveAndLoadPath()                     // Getter; M_SaveAndLoadPath
    {
        return M_SaveAndLoadPath;
    }
};

