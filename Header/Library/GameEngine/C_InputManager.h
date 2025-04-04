#pragma once
#include "solution.h"

// 키값을 정하기 위한 배열, 이런 방식으로 하면 컴파일 시점에 정해지므로 런타임에 유리함
// 이 배열을 별도로 전역 변수 있는 곳에 넣었다가 한참을 박았네..
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

class C_InputManager :
    public C_Singleton< C_InputManager>
{
    SINGLE(C_InputManager);

protected:
    vector<DS_KeyInfo>          STL_M_DS_KeyInfo;      // vector<DS_KeyInfo>
    DS_MouseInfo                M_DS_MouseInfo;        // DS_MouseInfo
    
public:
    // 초기화
    void MF_Initialize();

    void MF_Update();

    // KeyInfo Getter
    DS_KeyInfo MF_GetMouseInfo(E_KEY_TYPE _KeyType)
    {
        return STL_M_DS_KeyInfo[_KeyType];
    }

    // MouseInfo Getter
    DS_MouseInfo MF_GetMouseInfo()
    {
        return M_DS_MouseInfo;
    }
};

