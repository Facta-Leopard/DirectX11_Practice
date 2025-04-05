#pragma once
#include "C_Singleton.h"
class C_PathManager :
    public C_Singleton< C_PathManager>
{
    SINGLE(C_PathManager);

protected:
    wchar_t     M_ProjectPath[255];             // ������Ʈ ���͸� �ּ�
    wchar_t     M_SolutionPath[255];             // �ַ�� ���͸� �ּ�
    wchar_t     M_ResourcePath[255];             // Resource�� �ִ� ���͸� �ּ�
    wchar_t     M_SaveAndLoadPath[255];          // ����, ���� �ʿ�; Save �� Load ���͸� �ּ�

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

