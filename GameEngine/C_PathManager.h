#pragma once
#include "C_Singleton.h"
class C_PathManager :
    public C_Singleton< C_PathManager>
{
    SINGLE(C_PathManager);

protected:
    wchar_t     M_SolutionPath;             // 솔루션 디렉터리 주소
    wchar_t     M_BinaryPath;
    wchar_t     M_ResourcePath;             // Resource가 있는 디렉터리 주소
    wchar_t     M_SaveAndLoadPath;          // Save 및 Load 디렉터리 주소


};

