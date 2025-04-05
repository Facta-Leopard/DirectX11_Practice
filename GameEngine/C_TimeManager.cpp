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
	QueryPerformanceFrequency(&M_CurrentFrequency);				// 현재 1초당 카운팅 값; 하드웨어 고정된 값
	QueryPerformanceCounter(&M_TotalFrequencyBefore);			// 현재까지 누적된 카운팅 값
}

void C_TimeManager::MF_Update()
{
	QueryPerformanceCounter(&M_TotalFrequencyCurrent);			// 현재 키운팅 불러오기
	
	float T_Frequency = (float)(M_TotalFrequencyCurrent.QuadPart - M_TotalFrequencyBefore.QuadPart);	// 카운팅 차이 계산
	M_EngineDeltaTime = T_Frequency / (float)M_CurrentFrequency.QuadPart;									// Engine용 DeltaTime 계산 및 초기화

	M_TotalFrequencyBefore = M_TotalFrequencyCurrent;
	M_DeltaTime = M_EngineDeltaTime;							// DeltaTime 초기화

	++M_FPS;													// Frame당 FPS 1증가

	// 1초 관련 계산
	M_OneSecondTime += M_DeltaTime;								// 누적시간 계산
	if (1.f <= M_OneSecondTime)
	{
		HWND T_H_WindowHandle = C_GameEngine::SF_GetInstance()->MF_GetWindowHandle();
		wchar_t T_WindowTitleSubjectBuffer[255] = {};

		swprintf_s(T_WindowTitleSubjectBuffer, 255, L"FPS : %d, DeltaTime : %f", M_FPS, M_DeltaTime);		// 임시 버퍼에 델타타임 문자열 기재

		SetWindowText(T_H_WindowHandle, T_WindowTitleSubjectBuffer);				// 창에 문자열 표시

		M_OneSecondTime -= 1.f;														// 1초 기준점 초기화
		M_FPS = 0;																// FPS 초기화
	}



	// 향후, 스테이지 내 시간 흐름은 DeltaTime으로 구현하여 통제 내용 추가 예정



}
