#pragma once

class C_GameEngine :
	public C_Singleton<C_GameEngine>
{
	SINGLE(C_GameEngine)

private:
	// 윈도우 관련
	HINSTANCE				M_H_Instance;
	HWND					M_H_WindowHandle;
	Vector2					M_V2_Resolution;

	// FMOD 관련


	// 객체클래스 관련
	UINT					M_IDCount;			// 기존 코드를 클래스 아이디값을 사용한 방법 개선, 메모리 점유 유의미 감소

private:
	void MF_CreateWindow();

public:
	// 초기화함수
	void MF_Initialize();

	// Progress
	void MF_Prograss();

	// M_H_Window Getter
	HWND MF_GetWindowHandle()
	{
		return M_H_WindowHandle;
	}

	// MV2_Resolution Getter
	Vector2 MF_GetResolution()
	{
		return M_V2_Resolution;
	}

	// M_v2Resolution Setter
	//// Vector2
	void MF_SetResolution(Vector2 _Resolution)
	{
		M_V2_Resolution = _Resolution;
	}

	//// float
	void MF_SetResolution(float _Resolution_X, float _Resolution_Y)
	{
		M_V2_Resolution.x = _Resolution_X;
		M_V2_Resolution.y = _Resolution_Y;
	}

	// M_IDCount Getter
	UINT MF_GetIDCount()
	{
		return M_IDCount;
	}

	// M_IDCount Setter
	void MF_SetIDCount(UINT _Count)
	{
		M_IDCount = _Count;
	}
	// FMOD 관련

};