#pragma once
#include "C_Singleton.h"
class C_PathManager :
    public C_Singleton< C_PathManager>
{
    SINGLE(C_PathManager);

protected:
    wchar_t     M_ProjectPath[255];             // 프로젝트 디렉터리 주소
    wchar_t     M_SolutionPath[255];             // 솔루션 디렉터리 주소
    wchar_t     M_ResourcePath[255];             // Resource가 있는 디렉터리 주소
    wchar_t     M_SaveAndLoadPath[255];          // 향후, 정리 필요; Save 및 Load 디렉터리 주소

public:
    void MF_Initialize();

    wchar_t MF_GetProjectPath()
    {
        return M_ProjectPath[255];
    }

    wchar_t MF_GetSolutionPath()
    {
        return M_SolutionPath[255];
    }

    wchar_t MF_GetResourcePath()
    {
        return M_ResourcePath[255];
    }

    wchar_t MF_GetSaveAndLoadPath()
    {
        return M_SaveAndLoadPath[255];
    }
};

