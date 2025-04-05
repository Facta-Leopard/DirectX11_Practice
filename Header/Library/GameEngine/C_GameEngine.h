#pragma once

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


	// ��üŬ���� ����
	UINT					M_IDCount;			// ���� �ڵ带 Ŭ���� ���̵��� ����� ��� ����, �޸� ���� ���ǹ� ����

private:
	void MF_CreateWindow();

public:
	void MF_Initialize(HINSTANCE _HInstance, UINT _ResolutionX, UINT _ResoulutionY);		// �ʱ�ȭ �Լ�

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

	// ����, ���� ����
	// FMOD ����

};