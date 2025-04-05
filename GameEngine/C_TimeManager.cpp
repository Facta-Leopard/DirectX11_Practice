#include "pch.h"
#include "C_TimeManager.h"

C_TimeManager::C_TimeManager()
	: M_CurrentFrequency{}
	, M_TotalFrequencyBefore{}
	, M_TotalFrequencyCurrent{}
	, M_EngineTime(0.f)
	, M_EngineDeltaTime(0.f)
	, M_DeltaTime(0.f)
	, M_OneSecondTime(0.f)
	, M_FPS(0)

{
}

C_TimeManager::~C_TimeManager()
{

}

void C_TimeManager::MF_Initialize()
{
	QueryPerformanceFrequency(&M_CurrentFrequency);				// ���� 1�ʴ� ī���� ��; �ϵ���� ������ ��
	QueryPerformanceCounter(&M_TotalFrequencyBefore);			// ������� ������ ī���� ��
}

void C_TimeManager::MF_Update()
{
	QueryPerformanceCounter(&M_TotalFrequencyCurrent);			// ���� Ű���� �ҷ�����
	
	float T_Frequency = (float)(M_TotalFrequencyCurrent.QuadPart - M_TotalFrequencyBefore.QuadPart);	// ī���� ���� ���
	M_EngineDeltaTime = T_Frequency / (float)M_CurrentFrequency.QuadPart;									// Engine�� DeltaTime ��� �� �ʱ�ȭ

	M_TotalFrequencyBefore = M_TotalFrequencyCurrent;
	M_DeltaTime = M_EngineDeltaTime;							// DeltaTime �ʱ�ȭ

	++M_FPS;													// Frame�� FPS 1����

	// 1�� ���� ���
	M_OneSecondTime += M_DeltaTime;								// �����ð� ���
	if (1.f <= M_OneSecondTime)
	{
		HWND T_H_WindowHandle = C_GameEngine::SF_GetInstance()->MF_GetWindowHandle();
		wchar_t T_WindowTitleSubjectBuffer[255] = {};

		swprintf_s(T_WindowTitleSubjectBuffer, 255, L"FPS : %d, DeltaTime : %f", M_FPS, M_DeltaTime);		// �ӽ� ���ۿ� ��ŸŸ�� ���ڿ� ����

		SetWindowText(T_H_WindowHandle, T_WindowTitleSubjectBuffer);				// â�� ���ڿ� ǥ��

		M_OneSecondTime -= 1.f;														// 1�� ������ �ʱ�ȭ
		M_FPS = 0;																// FPS �ʱ�ȭ
	}



	// ����, �������� �� �ð� �帧�� DeltaTime���� �����Ͽ� ���� ���� �߰� ����



}
