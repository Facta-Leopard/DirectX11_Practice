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
    wchar_t     M_SaveAndLoadPath[255];                 // ����, ���� �ʿ�; Save And Load Directory Address

public:
    void MF_Initialize();


    // ����: �迭�� ���۷� ���� ���� �����ͷ� �Ͽ��� ��!
    // �迭�� �����ͷ� ǥ���� ����!
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

