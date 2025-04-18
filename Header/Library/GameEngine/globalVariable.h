#pragma once

// about KEY
struct DS_KeyInfo
{
	E_KEY_STATE		M_KeyState;				// E_KEY_STATE
	bool			M_WasPressed;			// bool
	// ���� ���� ���� GetAsyncKeyState()�� ���� �� �� �����Ƿ� ������ �� ������ ����
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

	// ����, Scroll�̳� �߰� ��ư �߰��ϸ� ���� ��
};

// ���ν����� ���� �����
//// �ٸ� ������ ���
////// Unreal Engine | 0.0001f ���� ����
////// Unity Engine | 0.0001f ���� �� ���
////// ���� ����� ���� ��� ������ ����Ͽ� 0.001f�� ������ �Ѵ�
constexpr float LL_G_ZeroScaleFloat = 0.001f;

// Vertex�� ���� ����ü
struct DS_Vertex
{
	Vector3			Position;		// Vector3; 3���� ��ǥ
	Vector2			PositionUV;		// Vector2; 2���� UV��ǥ
	Vector4			Color;			// Vector4; RGBA
};

// ���Ͽ� ��� ������ ������, �޸� ���Ŀ� ���� ������� �� �浹ü ���� ���� �� Ȯ���� ����ؼ� ������ ����ü�� ����� ��
//union U_HashInfo
//{
//
//};

// ���⺤Ʈ�� �����ϰ��� ���������, ���並 ����غ� ��� �迭�� �����ϴ� ���� ������� ���� �� SIMD�� �����Ƿ� ������ �ߵ� ������
// �̰� ������ ���� �������ڴ� �ǹ̿��� ���� ��..
//struct DS_Vector3_Direction					// Vector3�� ��� 3���� ������ �ִ� ����ü
//{
//	Vector3				M_DirectionRight;
//	Vector3				M_DirectionUp;
//	Vector3				M_DirectionFront;
//};