#include "pch.h"
#include "C_PathManager.h"

C_PathManager::C_PathManager()
	: M_ProjectPath_s{}
	, M_SolutionPath_s{}
	, M_ResourcePath_s{}
	, M_SaveAndLoadPath_s{}
{

}

C_PathManager::~C_PathManager()
{

}

void C_PathManager::MF_Initialize()
{
	constexpr int T_BufferSize = 255;				// ���۷� ����� ������ ����ũ�� ����; ���� ���̺귯�� ȣȯ������ ���Ͽ� 255�� ������;
	wchar_t T_Literals[T_BufferSize] = {};			// ���ڿ� �迭 ���� �� �ʱ�ȭ

		GetCurrentDirectory(T_BufferSize, T_Literals);		// GetCurrentDirectoryW�� ����ϳ� ����ߴµ�.. �˾Ƽ� ���ָ� ��..

	// ����, ��θ� �ٸ� ������ �ٲپ Ȯ! �ϰ� ���� �� �ٲ�� ��Ŀ������ ������ ������� ������?
	wcscpy_s(M_ProjectPath_s, T_Literals);					// Project ���� ��ġ�� ���ڿ� ����

	// Solution ���� ��ġ ��� ���
	wcscpy_s(M_SolutionPath_s, M_ProjectPath_s);
	wcscat_s(M_ProjectPath_s, L"\\");
	for (size_t i = wcslen(M_SolutionPath_s); 0 < i; --i)
	{
		if (L'\\' == M_SolutionPath_s[i])
		{
			M_SolutionPath_s[i] = L'\0';
			break;
		}
	}

	// ResourcePath ���� ��ġ ��� ���
	wcscpy_s(M_ResourcePath_s, M_SolutionPath_s);
	wcscat_s(M_SolutionPath_s, L"\\");

	wcscat_s(M_ResourcePath_s, 255, L"\\Resource\\");			// Solution ���� ��ġ�� ���� ������

	// ����, SaveAndLoad ���� ��ġ ��� ���


}
