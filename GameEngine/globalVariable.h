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
	bool			M_WasPressed;			// bool
	bool			M_IsPressed;			// bool
};

//// MouseRightButton
struct DS_MouseRightButton
{
	bool			M_WasPressed;			// bool
	bool			M_IsPressed;			// bool
};


struct DS_MouseInfo
{
	// Mouse Pos
	Vector2					M_MousePos;					// Vector2
	Vector2					M_MousePosBefore;			// Vector2

	// Drag Direction
	Vector2					M_V2_Direction;				// Vector2

	// Left Button
	DS_MouseLeftButton		M_DS_MouseLeftButton;		// DS_MouseLeftButton

	// Right Button
	DS_MouseRightButton		M_DS_MouseRightButton;		// DS_MouseRightButton

	// 향후, Scroll이나 추가 버튼 추가하면 좋을 듯
};


// 유니온 방식 쓰려고 했으나, 메모리 정렬에 따른 오버헤드 및 충돌체 개수 증가 등 확상성을 고려해서 윈도우 구조체를 쓰기로 함
//union U_HashInfo
//{
//
//};

// 방향벡트를 관리하고자 만들었으나, 검토를 계속해본 결과 배열로 관리하는 것이 오버헤드 관리 및 SIMD에 좋으므로 과감히 중도 포기함
// 이건 뻘짓한 것을 잊지말자는 의미에서 남겨 둠..
//struct DS_Vector3_Direction					// Vector3를 멤버 3개를 가지고 있는 구조체
//{
//	Vector3				M_DirectionRight;
//	Vector3				M_DirectionUp;
//	Vector3				M_DirectionFront;
//};