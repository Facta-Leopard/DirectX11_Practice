#pragma once
#include "C_Singleton.h"

#include"define.h"

class C_PathManager :
    public C_Singleton< C_PathManager>
{
    SINGLE(C_PathManager);

private:
    wchar_t     M_ProjectPath_s[255];                     // Project Directory Address
    wchar_t     M_SolutionPath_s[255];                    // Solution Directory Address
    wchar_t     M_ResourcePath_s[255];                    // Resource Directory Address
    wchar_t     M_SaveAndLoadPath_s[255];                 // ����, ���� �ʿ�; Save And Load Directory Address

public:
    HRESULT MF_Initialize();


    // ����: �迭�� ���۷� ���� ���� �����ͷ� �Ͽ��� ��!
    // �迭�� �����ͷ� ǥ���� ����!
    inline wchar_t* MF_Get_ProjectPath_s()                         // Getter; M_ProjectPath_s
    {
        return M_ProjectPath_s;
    }

    inline wchar_t* MF_Get_SolutionPath_s()                        // Getter; M_SolutionPath_s
    {
        return M_SolutionPath_s;
    }

    inline wchar_t* MF_Get_ResourcePath_s()                        // Getter; M_ResourcePath_s
    {
        return M_ResourcePath_s;
    }

    inline wchar_t* MF_Get_SaveAndLoadPath_s()                     // Getter; M_SaveAndLoadPath_s
    {
        return M_SaveAndLoadPath_s;
    }
};

