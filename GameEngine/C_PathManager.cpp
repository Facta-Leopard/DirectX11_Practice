#include "pch.h"
#include "C_PathManager.h"

C_PathManager::C_PathManager()
	: M_ProjectPath{}
	, M_SolutionPath{}
	, M_ResourcePath{}
	, M_SaveAndLoadPath{}
{

}

C_PathManager::~C_PathManager()
{

}

void C_PathManager::MF_Initialize()
{
	constexpr int T_BufferSize = 255;				// 버퍼로 사용할 임의의 버퍼크기 설정; 기존 하이브러리 호환성으로 인하여 255로 고정함;
	wchar_t T_Literal[T_BufferSize] = {};			// 문자열 배열 선언 및 초기화

	// 경로 오버플로우 체크
	wchar_t T_OverflowCheckBuffer[32767] = {}; // int 최대치 2147483647는 배열 자체가 너무 실어서 안되므로, wchar_t 최대치인 32767 적용; Windows System 이 사용하는 UNICODE API의 최대치임

	GetCurrentDirectory(32767, T_OverflowCheckBuffer);

	if (wcslen(T_OverflowCheckBuffer) > 255)
	{
		POPUP_DEBUG(L"Path Overflow Threat!", L"in C_PathManager::MF_Initialize(), Beffer Size Change");
		POPUP(L"Path Overflow Threat!", L"Reinstall on Short Path Directory");
	}
	else
	{
		GetCurrentDirectory(T_BufferSize, T_Literal);		// GetCurrentDirectoryW로 써야하나 고민했는데.. 알아서 해주면 뭐..
	}

	// 향후, 경로를 다른 곳에서 바꾸어서 확! 하고 몽땅 다 바뀌는 메커니즘을 넣으면 재미있지 않을까?
	wcscpy_s(M_ProjectPath, T_Literal);					// Project 폴더 위치를 문자열 복사

	// Solution 폴더 위치 경로 계산
	wcscpy_s(M_SolutionPath, M_ProjectPath);
	wcscat_s(M_ProjectPath, L"\\");
	for (int i = wcslen(M_SolutionPath); 0 <= i; --i)
	{
		if (L'\\' == M_SolutionPath[i])
		{
			M_SolutionPath[i] = L'\0';
			break;
		}
	}

	// ResourcePath 폴더 위치 경로 계산
	wcscpy_s(M_ResourcePath, M_SolutionPath);
	wcscat_s(M_SolutionPath, L"\\");

	wcscat_s(M_ResourcePath, 255, L"\\Resource\\");			// Solution 폴더 위치에 글자 붙히기

	// 향후, SaveAndLoad 폴더 위치 경로 계산


}
