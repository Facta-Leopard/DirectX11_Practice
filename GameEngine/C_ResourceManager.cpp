#include "pch.h"
#include "C_ResourceManager.h"

C_ResourceManager::C_ResourceManager()
	: STL_M_ImageSet{}
{
	// .rsc 파일이 저장되어 있는 기본 위치 설정
	wchar_t wchar_T_Path_s[255] = {};
	wstring wstring_BasicPath = {};
	GetCurrentDirectory(255, wchar_T_Path_s);
	wcscat_s(wchar_T_Path_s, 255, L"\\Resource\\");
	wstring_BasicPath = wchar_T_Path_s;
}

C_ResourceManager::~C_ResourceManager()
{

}

HRESULT C_ResourceManager::MF_Initialize()
{
	return E_NOTIMPL;
}
