#pragma once

class C_GameEngine: public C_Singleton<C_GameEngine>
{
	// 생성자 및 소멸자 포함된 매크로 사용
	SINGLE(C_GameEngine);

private:
	// 윈도우 관련
	HINSTANCE				MH_Instance;
	HWND					MH_Window;
	Vector2					MV2_Resolution;

	// FMOD 관련

private:
	int MF_CreateWindow();

public:
	int MF_Innitialize();				// 초기화함수

	void MF_Prograss();

	Vector2 MF_GetResolution()
	{
		return MV2_Resolution;
	}

	Vector2 MF_SetResolution(Vector2 _Resolution)
	{
		MV2_Resolution = _Resolution;
	}

	// FMOD 관련

};