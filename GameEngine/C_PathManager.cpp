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
	constexpr int T_BufferSize = 255;				// ���۷� ����� ������ ����ũ�� ����; ���� ���̺귯�� ȣȯ������ ���Ͽ� 255�� ������;
	wchar_t T_Literal[T_BufferSize] = {};			// ���ڿ� �迭 ���� �� �ʱ�ȭ

		GetCurrentDirectory(T_BufferSize, T_Literal);		// GetCurrentDirectoryW�� ����ϳ� ����ߴµ�.. �˾Ƽ� ���ָ� ��..

	// ����, ��θ� �ٸ� ������ �ٲپ Ȯ! �ϰ� ���� �� �ٲ�� ��Ŀ������ ������ ������� ������?
	wcscpy_s(M_ProjectPath, T_Literal);					// Project ���� ��ġ�� ���ڿ� ����

	// Solution ���� ��ġ ��� ���
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

	// ResourcePath ���� ��ġ ��� ���
	wcscpy_s(M_ResourcePath, M_SolutionPath);
	wcscat_s(M_SolutionPath, L"\\");

	wcscat_s(M_ResourcePath, 255, L"\\Resource\\");			// Solution ���� ��ġ�� ���� ������

	// ����, SaveAndLoad ���� ��ġ ��� ���


}
