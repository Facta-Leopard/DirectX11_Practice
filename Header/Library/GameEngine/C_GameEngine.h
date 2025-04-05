#pragma once

class C_GameEngine :
	public C_Singleton<C_GameEngine>
{
	SINGLE(C_GameEngine)

private:
	// 윈도우 관련
	HINSTANCE				M_H_Instance;			// HINSTANCE
	HWND					M_H_WindowHandle;		// HWND
	Vector2					M_V2_Resolution;		// Vector2, DirectX와의 호환성을 위해 UINT 대신 float을 쓰는 듯

	// FMOD 관련


	// 객체클래스 관련
	UINT					M_IDCount;			// 기존 코드를 클래스 아이디값을 사용한 방법 개선, 메모리 점유 유의미 감소

private:
	void MF_CreateWindow();

public:
	void MF_Initialize(HINSTANCE _HInstance, UINT _ResolutionX, UINT _ResoulutionY);		// 초기화 함수

	void MF_Prograss();


	inline HWND MF_GetWindowHandle()														// Getter; 
	{
		return M_H_WindowHandle;
	}

	inline  Vector2 MF_GetResolution()														// Getter; 
	{
		return M_V2_Resolution;
	}

	inline void MF_SetResolution(Vector2 _Resolution)										// Setter; M_V2_Resolution; Overloaded
	{
		M_V2_Resolution = _Resolution;
	}

	inline void MF_SetResolution(float _Resolution_X, float _Resolution_Y)					// Setter; M_V2_Resolution; Overloaded
	{
		M_V2_Resolution.x = _Resolution_X;
		M_V2_Resolution.y = _Resolution_Y;
	}

	inline UINT MF_GetIDCount()																// Getter; M_IDCount
	{
		return M_IDCount;
	}

	inline void MF_SetIDCount(UINT _Count)													// Setter; M_IDCount
	{
		M_IDCount = _Count;
	}

	// 향후, 구현 예정
	// FMOD 관련

};