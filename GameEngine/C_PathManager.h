#pragma once
#include "C_Singleton.h"
class C_PathManager :
    public C_Singleton< C_PathManager>
{
    SINGLE(C_PathManager);

protected:
    wchar_t     M_SolutionPath;             // �ַ�� ���͸� �ּ�
    wchar_t     M_BinaryPath;
    wchar_t     M_ResourcePath;             // Resource�� �ִ� ���͸� �ּ�
    wchar_t     M_SaveAndLoadPath;          // Save �� Load ���͸� �ּ�


};

