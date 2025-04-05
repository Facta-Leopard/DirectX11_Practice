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
    wchar_t     M_SaveAndLoadPaths[255];                 // ����, ���� �ʿ�; Save And Load Directory Address

public:
    void MF_Initialize();


    // ����: �迭�� ���۷� ���� ���� �����ͷ� �Ͽ��� ��!
    // �迭�� �����ͷ� ǥ���� ����!
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

