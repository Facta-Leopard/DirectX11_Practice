#pragma once

#include "C_Singleton.h"

#include "global.h"

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
	FMOD::System* P_M_F_System;						// FMOD::System*; 유의! WinAPI System등 기타 다른 것들과 충돌을 피하기 위해 namespace를 통해 구분함

	// 객체클래스 관련
	UINT					M_IDCount;				// C_Entity의 객체구별용으로 사용; 기존 코드를 클래스 아이디값을 사용한 방법 개선; 메모리 점유 유의미 감소

private:
	void MF_CreateWindow();

public:
	HRESULT MF_Initialize(HINSTANCE _HInstance, UINT _ResolutionX, UINT _ResoulutionY);		// 초기화 함수

	void MF_Prograss();

	inline HWND MF_Get_WindowHandle()														// Getter; 
	{
		return M_H_WindowHandle;
	}

	inline  Vector2 MF_Get_Resolution()														// Getter; 
	{
		return M_V2_Resolution;
	}

	inline void MF_Set_Resolution(Vector2 _Resolution)										// Setter; Overloaded; M_V2_Resolution
	{
		M_V2_Resolution = _Resolution;
	}

	inline void MF_Set_Resolution(float _Resolution_X, float _Resolution_Y)					// Setter; Overloaded; M_V2_Resolution
	{
		M_V2_Resolution.x = _Resolution_X;
		M_V2_Resolution.y = _Resolution_Y;
	}

	inline FMOD::System* Get_FMODSystem()													// Getter; P_M_F_System
	{
		return P_M_F_System;
	}

	inline UINT MF_Get_IDCount()															// Getter; M_IDCount
	{
		return M_IDCount;
	}

	inline void MF_Set_IDCount(UINT _Count)													// Setter; M_IDCount; 객체 구별용 아이디이므로, 반환값을 ++함
	{
		M_IDCount = _Count;
	}
};