#pragma once

#include "C_Singleton.h"

#include "global.h"

class C_GameEngine :
	public C_Singleton<C_GameEngine>
{
	SINGLE(C_GameEngine)

private:
	// ������ ����
	HINSTANCE				M_H_Instance;			// HINSTANCE
	HWND					M_H_WindowHandle;		// HWND
	Vector2					M_V2_Resolution;		// Vector2, DirectX���� ȣȯ���� ���� UINT ��� float�� ���� ��

	// FMOD ����
	FMOD::System* P_M_F_System;						// FMOD::System*; ����! WinAPI System�� ��Ÿ �ٸ� �͵�� �浹�� ���ϱ� ���� namespace�� ���� ������

	// ��üŬ���� ����
	UINT					M_IDCount;				// C_Entity�� ��ü���������� ���; ���� �ڵ带 Ŭ���� ���̵��� ����� ��� ����; �޸� ���� ���ǹ� ����

private:
	void MF_CreateWindow();

public:
	HRESULT MF_Initialize(HINSTANCE _HInstance, UINT _ResolutionX, UINT _ResoulutionY);		// �ʱ�ȭ �Լ�

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

	inline void MF_Set_IDCount(UINT _Count)													// Setter; M_IDCount; ��ü ������ ���̵��̹Ƿ�, ��ȯ���� ++��
	{
		M_IDCount = _Count;
	}
};