#include "pch.h"
#include "C_InputManager.h"

void C_InputManager::MF_Initialize()
{
	// 키보드 초기화
	// E_KEYTYPE을 vector 자료형의 순서에 맞추는 트릭을 써서 초기화
	for (size_t n = _KEY_Q; n < _KEY_END ; ++n)
	{
		// push_back할 때, 이렇게 구조체 안의 값을 나열해서 적는 것은 익숙하지가 않네..
		STL_M_DS_KeyInfo.push_back(DS_KeyInfo{_KEY_NONE, false});
	}

	// 마우스 초기화
	//// 마우스 좌표를 담을 임시 객체
	POINT T_MousePos;
	if (!GetCursorPos(&T_MousePos))	// 마우스 절대좌표 가져오는 WInAPI Function 사용
	{
		POPUP(L"MousePos Initializing Failed", L"C_KeyManager::MF_Initialize() 내 GetCursorPos() 실패");
	}

	if (!ScreenToClient(C_GameEngine::SF_GetInstance()->MF_GetWindowHandle(), &T_MousePos))	// 마우스 좌표를 창 기준으로 상대좌표로 변환해주는 WinAPI Function 사용
	{
		POPUP(L"MousePos Initializing Failed", L"C_KeyManager::MF_Initialize() ScreenToClient() 실패");
	}

	M_DS_MouseInfo.M_MousePos = (Vector2)((float)T_MousePos.x, (float)T_MousePos.y);			// 현재 마우스 좌표 설정
	M_DS_MouseInfo.M_MousePosBefore = (Vector2)((float)T_MousePos.x, (float)T_MousePos.y);	// 이전 마우스 좌표로 똑같이 설정
}

void C_InputManager::MF_Update()
{
	// 실행창이 포커스 중일 때
	if (GetFocus() == C_GameEngine::SF_GetInstance()->MF_GetWindowHandle())		// 포커스 상태를 확인하기 위한 WinAPI Function 사용
	{
		//// for (auto& n : STL_M_DS_KeyInfo) 형식인 loop문으로 하면 GetAsyncKeyState()가 되지 않음..
		//// loop문은 indexing에는 못 쓴다는 사실을 알았다.. 몇 시간을 박은 거야 진짜..
		for (size_t i = 0; i < STL_M_DS_KeyInfo.size(); ++i)
		{
			////// 현재 키가 눌려있을 때
			if (GetAsyncKeyState(UINT_KeyValue[i]) & 0x8001)
			{
				//////// 이전에 키가 눌려있었을 때
				if (STL_M_DS_KeyInfo[i].M_WasPressed)
				{
					STL_M_DS_KeyInfo[i].M_KeyState = _KEY_PRESSED;
				}
				//////// 이전에 키가 눌려있지 않았을 때
				else
				{
					STL_M_DS_KeyInfo[i].M_KeyState = _KEY_TAP;

				}

			}
			////// 현재 키가 눌려있지 않을 때
			else
			{
				//////// 이전에는 키가 눌려있었을 때
				if (STL_M_DS_KeyInfo[i].M_WasPressed)
				{
					STL_M_DS_KeyInfo[i].M_KeyState = _KEY_RELEASED;

				}
				/////// 이전에도 키가 눌려있지 않았을 때
				else
				{
					STL_M_DS_KeyInfo[i].M_KeyState = _KEY_NONE;

				}
			}
		}

		//// 마우스 좌표 갱신
		M_DS_MouseInfo.M_MousePosBefore = M_DS_MouseInfo.M_MousePos;

		POINT T_MousePos;
		if (!GetCursorPos(&T_MousePos))	// 마우스 절대좌표 가져오는 WInAPI Function 사용
		{
			POPUP(L"MousePos Initializing Failed", L"C_KeyManager::MF_Update() 내 GetCursorPos() 실패");
		}

		if (!ScreenToClient(C_GameEngine::SF_GetInstance()->MF_GetWindowHandle(), &T_MousePos))			// 마우스 좌표를 창 기준으로 상대좌표로 변환해주는 WinAPI Function 사용
		{
			POPUP(L"MousePos Initializing Failed", L"C_KeyManager::MF_Update() ScreenToClient() 실패");
		}

		M_DS_MouseInfo.M_MousePos = (Vector2)((float)T_MousePos.x, (float)T_MousePos.y);								// 현재 마우스 좌표 설정

		M_DS_MouseInfo.M_V2_Direction = M_DS_MouseInfo.M_MousePos - M_DS_MouseInfo.M_MousePosBefore;	// 마우스 방향벡터 계산
	}

	// 실행창이 포커스 중이 아닐 때
	else
	{
		//// 모든 키를 아무 것도 아닌 상태로 전환하고 키 눌림 상태를 false로 지정
		for (size_t i = 0; i < STL_M_DS_KeyInfo.size(); ++i)
		{
			STL_M_DS_KeyInfo[i].M_KeyState = _KEY_NONE;
			STL_M_DS_KeyInfo[i].M_WasPressed = false;

		}

		//// 마우스 좌표로 인한 문제가 발생하지 않도록 좌표를 강제 함
		M_DS_MouseInfo.M_MousePosBefore = (Vector2)((float)0xffffffff, (float)0xffffffff);
		M_DS_MouseInfo.M_MousePos = (Vector2)((float)0xffffffff, (float)0xffffffff);
	}
}

// 굳이 마우스 좌표가 창 밖에 나갔는지 확인할 필요가 있을까?
// 향후, 필요할 때 추가하는 걸로 하자.