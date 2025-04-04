#include "pch.h"
#include "C_InputManager.h"

void C_InputManager::MF_Initialize()
{
	// Ű���� �ʱ�ȭ
	// E_KEYTYPE�� vector �ڷ����� ������ ���ߴ� Ʈ���� �Ἥ �ʱ�ȭ
	for (size_t n = _KEY_Q; n < _KEY_END ; ++n)
	{
		// push_back�� ��, �̷��� ����ü ���� ���� �����ؼ� ���� ���� �ͼ������� �ʳ�..
		STL_M_DS_KeyInfo.push_back(DS_KeyInfo{_KEY_NONE, false});
	}

	// ���콺 �ʱ�ȭ
	//// ���콺 ��ǥ�� ���� �ӽ� ��ü
	POINT T_MousePos;
	if (!GetCursorPos(&T_MousePos))	// ���콺 ������ǥ �������� WInAPI Function ���
	{
		POPUP(L"MousePos Initializing Failed", L"C_KeyManager::MF_Initialize() �� GetCursorPos() ����");
	}

	if (!ScreenToClient(C_GameEngine::SF_GetInstance()->MF_GetWindowHandle(), &T_MousePos))	// ���콺 ��ǥ�� â �������� �����ǥ�� ��ȯ���ִ� WinAPI Function ���
	{
		POPUP(L"MousePos Initializing Failed", L"C_KeyManager::MF_Initialize() ScreenToClient() ����");
	}

	M_DS_MouseInfo.M_MousePos = (Vector2)((float)T_MousePos.x, (float)T_MousePos.y);			// ���� ���콺 ��ǥ ����
	M_DS_MouseInfo.M_MousePosBefore = (Vector2)((float)T_MousePos.x, (float)T_MousePos.y);	// ���� ���콺 ��ǥ�� �Ȱ��� ����
}

void C_InputManager::MF_Update()
{
	// ����â�� ��Ŀ�� ���� ��
	if (GetFocus() == C_GameEngine::SF_GetInstance()->MF_GetWindowHandle())		// ��Ŀ�� ���¸� Ȯ���ϱ� ���� WinAPI Function ���
	{
		//// for (auto& n : STL_M_DS_KeyInfo) ������ loop������ �ϸ� GetAsyncKeyState()�� ���� ����..
		//// loop���� indexing���� �� ���ٴ� ����� �˾Ҵ�.. �� �ð��� ���� �ž� ��¥..
		for (size_t i = 0; i < STL_M_DS_KeyInfo.size(); ++i)
		{
			////// ���� Ű�� �������� ��
			if (GetAsyncKeyState(UINT_KeyValue[i]) & 0x8001)
			{
				//////// ������ Ű�� �����־��� ��
				if (STL_M_DS_KeyInfo[i].M_WasPressed)
				{
					STL_M_DS_KeyInfo[i].M_KeyState = _KEY_PRESSED;
				}
				//////// ������ Ű�� �������� �ʾ��� ��
				else
				{
					STL_M_DS_KeyInfo[i].M_KeyState = _KEY_TAP;

				}

			}
			////// ���� Ű�� �������� ���� ��
			else
			{
				//////// �������� Ű�� �����־��� ��
				if (STL_M_DS_KeyInfo[i].M_WasPressed)
				{
					STL_M_DS_KeyInfo[i].M_KeyState = _KEY_RELEASED;

				}
				/////// �������� Ű�� �������� �ʾ��� ��
				else
				{
					STL_M_DS_KeyInfo[i].M_KeyState = _KEY_NONE;

				}
			}
		}

		//// ���콺 ��ǥ ����
		M_DS_MouseInfo.M_MousePosBefore = M_DS_MouseInfo.M_MousePos;

		POINT T_MousePos;
		if (!GetCursorPos(&T_MousePos))	// ���콺 ������ǥ �������� WInAPI Function ���
		{
			POPUP(L"MousePos Initializing Failed", L"C_KeyManager::MF_Update() �� GetCursorPos() ����");
		}

		if (!ScreenToClient(C_GameEngine::SF_GetInstance()->MF_GetWindowHandle(), &T_MousePos))			// ���콺 ��ǥ�� â �������� �����ǥ�� ��ȯ���ִ� WinAPI Function ���
		{
			POPUP(L"MousePos Initializing Failed", L"C_KeyManager::MF_Update() ScreenToClient() ����");
		}

		M_DS_MouseInfo.M_MousePos = (Vector2)((float)T_MousePos.x, (float)T_MousePos.y);								// ���� ���콺 ��ǥ ����

		M_DS_MouseInfo.M_V2_Direction = M_DS_MouseInfo.M_MousePos - M_DS_MouseInfo.M_MousePosBefore;	// ���콺 ���⺤�� ���
	}

	// ����â�� ��Ŀ�� ���� �ƴ� ��
	else
	{
		//// ��� Ű�� �ƹ� �͵� �ƴ� ���·� ��ȯ�ϰ� Ű ���� ���¸� false�� ����
		for (size_t i = 0; i < STL_M_DS_KeyInfo.size(); ++i)
		{
			STL_M_DS_KeyInfo[i].M_KeyState = _KEY_NONE;
			STL_M_DS_KeyInfo[i].M_WasPressed = false;

		}

		//// ���콺 ��ǥ�� ���� ������ �߻����� �ʵ��� ��ǥ�� ���� ��
		M_DS_MouseInfo.M_MousePosBefore = (Vector2)((float)0xffffffff, (float)0xffffffff);
		M_DS_MouseInfo.M_MousePos = (Vector2)((float)0xffffffff, (float)0xffffffff);
	}
}

// ���� ���콺 ��ǥ�� â �ۿ� �������� Ȯ���� �ʿ䰡 ������?
// ����, �ʿ��� �� �߰��ϴ� �ɷ� ����.