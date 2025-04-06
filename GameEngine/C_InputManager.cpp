#include "pch.h"
#include "C_InputManager.h"

// Ű���� ���ϱ� ���� �迭, �̷� ������� �ϸ� ������ ������ �������Ƿ� ��Ÿ�ӿ� ������
// �� �迭�� ������ ���� ���� �ִ� ���� �־��ٰ� ������ �ھҳ�..
UINT UINT_KeyValue[_KEY_END] =
{
	'Q', 'W', 'E', 'R', 'T', 'Y',
	'A', 'S', 'D', 'F', 'G', 'H',
	'Z', 'X', 'C',  'V',  'B',  'N', 'M',

	VK_RETURN,
	VK_ESCAPE,
	VK_LSHIFT,
	VK_MENU,
	VK_CONTROL,
	VK_SPACE,

	VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT,

	VK_NUMPAD0,
	VK_NUMPAD1,
	VK_NUMPAD2,
	VK_NUMPAD3,
	VK_NUMPAD4,
	VK_NUMPAD5,
	VK_NUMPAD6,
	VK_NUMPAD7,
	VK_NUMPAD8,
	VK_NUMPAD9,

	VK_LBUTTON,
	VK_RBUTTON,
};

C_InputManager::C_InputManager()
{

}

C_InputManager::~C_InputManager()
{

}

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
	if (NULL == GetCursorPos(&T_MousePos))					// ���콺 ������ǥ �������� WInAPI Function ���
	{
		POPUP_DEBUG(L"MousePos Initializing Failed", L"in C_InputManager::MF_Initialize(), NULL == GetCursorPos()");
	}

	HWND T_H_Window = C_GameEngine::SF_GetInstance()->MF_GetWindowHandle();

	if (NULL == ScreenToClient(T_H_Window, &T_MousePos))	// ���콺 ��ǥ�� â �������� �����ǥ�� ��ȯ���ִ� WinAPI Function ���
	{
		POPUP_DEBUG(L"MousePos Initializing Failed", L"in C_InputManager::MF_Initialize(), NULL == ScreenToClient()");
	}

	Vector2 T_Mousepos = (Vector2)(C_GameEngine::SF_GetInstance()->MF_GetResolution());
	T_Mousepos /= 2;

	M_DS_MouseInfo.M_MousePos = T_Mousepos;															// ���� ���콺 ��ǥ �ʱ���ǥ �ػ� �������� ���� ����
	// M_DS_MouseInfo.M_MousePos = (Vector2)((float)T_MousePos.x, (float)T_MousePos.y);				// �̷��� �ϸ� �ʱ� ���� â ����� ��ġ�� ����� ȭ�� ��Ʈ�� �Ұ�	
	M_DS_MouseInfo.M_MousePosBefore = T_Mousepos;													// ���� ���콺 ��ǥ �ʱ���ǥ �ػ� �������� ���� ����
	// M_DS_MouseInfo.M_MousePosBefore = (Vector2)((float)T_MousePos.x, (float)T_MousePos.y);		// �̷��� �ϸ� �ʱ� ���� â ����� ��ġ�� ����� ȭ�� ��Ʈ�� �Ұ�
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
		if (NULL == GetCursorPos(&T_MousePos))	// ���콺 ������ǥ �������� WInAPI Function ���
		{
			POPUP_DEBUG(L"MousePos Initializing Failed", L"in C_KeyManager::MF_Update(), NULL == GetCursorPos()");
		}

		if (NULL == ScreenToClient(C_GameEngine::SF_GetInstance()->MF_GetWindowHandle(), &T_MousePos))			// ���콺 ��ǥ�� â �������� �����ǥ�� ��ȯ���ִ� WinAPI Function ���
		{
			POPUP_DEBUG(L"MousePos Initializing Failed", L"in C_KeyManager::MF_Update() ScreenToClient(), NULL == ScreenToClient(");
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

		//// ���콺 Ŭ�� �κ��� false�� ��
		M_DS_MouseInfo.M_DS_MouseLeftButton.M_WasPressed = false;
		M_DS_MouseInfo.M_DS_MouseLeftButton.M_IsPressed = false;

	}
}

// ���� ���콺 ��ǥ�� â �ۿ� �������� Ȯ���� �ʿ䰡 ������?
// ����, �ʿ��� �� �߰��ϴ� �ɷ� ����.