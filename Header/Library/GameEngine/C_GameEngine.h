#pragma once

#include "Solution.h"

class C_GameEngine: public C_Singleton<C_GameEngine>
{
	// 생성자 및 소멸자 포함된 매크로 사용
	SINGLE(C_GameEngine);

private:
	// 윈도우 관련
	HINSTANCE				M_H_Instance;		// HINSTANCE
	HWND					M_H_Window;			// HWND
	Vector2					M_V2_Resolution;	// Vector2

	// FMOD 관련

private:
	int MF_CreateWindow();

public:
	int MF_Innitialize();

	void MF_Prograss();

	Vector2 MF_GetResolution()
	{
		return M_V2_Resolution;
	}

	Vector2 MF_SetResolution(Vector2 _Resolution)
	{
		M_V2_Resolution = _Resolution;
	}

	// FMOD 관련

};