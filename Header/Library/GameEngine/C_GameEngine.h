#pragma once

class C_GameEngine: public C_Singleton<C_GameEngine>
{
	// ������ �� �Ҹ��� ���Ե� ��ũ�� ���
	SINGLE(C_GameEngine);

private:
	// ������ ����
	HINSTANCE				MH_Instance;
	HWND					MH_Window;
	Vector2					MV2_Resolution;

	// FMOD ����

private:
	int MF_CreateWindow();

public:
	int MF_Innitialize();				// �ʱ�ȭ�Լ�

	void MF_Prograss();

	Vector2 MF_GetResolution()
	{
		return MV2_Resolution;
	}

	Vector2 MF_SetResolution(Vector2 _Resolution)
	{
		MV2_Resolution = _Resolution;
	}

	// FMOD ����

};