#pragma once
#include "C_Singleton.h"
class C_PathManager :
    public C_Singleton< C_PathManager>
{
    SINGLE(C_PathManager);

protected:
    wchar_t     M_ProjectPaths[255];                     // Project Directory Address
    wchar_t     M_SolutionPaths[255];                    // Solution Directory Address
    wchar_t     M_ResourcePaths[255];                    // Resource Directory Address
    wchar_t     M_SaveAndLoadPaths[255];                 // 향후, 정리 필요; Save And Load Directory Address

public:
    void MF_Initialize();


    // 유의: 배열을 버퍼로 읽을 때는 포인터로 하여야 함!
    // 배열은 포인터로 표현이 가능!
    inline wchar_t* MF_GetProjectPaths()                         // Getter; M_ProjectPaths
    {
        return M_ProjectPaths;
    }

    inline wchar_t* MF_GetSolutionPaths()                        // Getter; M_SolutionPaths
    {
        return M_SolutionPaths;
    }

    inline wchar_t* MF_GetResourcePaths()                        // Getter; M_ResourcePaths
    {
        return M_ResourcePaths;
    }

    inline wchar_t* MF_GetSaveAndLoadPaths()                     // Getter; M_SaveAndLoadPaths
    {
        return M_SaveAndLoadPaths;
    }
};

