#pragma once

// about KEY
struct DS_KeyInfo
{
	E_KEY_STATE		M_KeyState;				// E_KEY_STATE
	bool			M_WasPressed;			// bool
	// 현재 눌린 것은 GetAsyncKeyState()를 통해 알 수 있으므로 별도로 쓸 이유가 없음
};




// about Mouse
//// MouseLeftButton
struct DS_MouseLeftButton
{
	Vector2			M_V2_LeftButton;		// Vector2
	bool			M_WasPressed;			// bool
	bool			M_IsPressed;			// bool
};

//// MouseRightButton
struct DS_MouseRightButton
{
	Vector2			M_V2_RightButton;		// Vector2
	bool			M_WasPressed;			// bool
	bool			M_IsPressed;			// bool
};


struct DS_MouseInfo
{
	// Mouse Pos
	Vector2					M_MousePos;					// Vector2
	Vector2					M_MousePosBefore;			// Vector2

	// Left Button
	DS_MouseLeftButton		M_DS_MouseLeftButton;		// DS_MouseLeftButton

	// Right Button
	DS_MouseRightButton		M_DS_MouseRightButton;		// DS_MouseRightButton

	// Drag Direction
	Vector2					M_V2_Direction;				// Vector2

	// 향후, Scroll이나 추가 버튼 추가하면 좋을 듯
};