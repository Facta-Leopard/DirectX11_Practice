#pragma once

#include "DirectXMath.h"

#include "define.h"

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

// 제로스케일 방어용 상수값
//// 다른 엔진의 경우
////// Unreal Engine | 0.0001f 이하 차단
////// Unity Engine | 0.0001f 이하 시 경고
////// 내가 만드는 것은 상기 사항을 고려하여 0.001f의 값으로 한다
constexpr float G_LL_ZeroScaleFloat = 0.001f;

// Bind 전용 구조체
//// Vertex용 구조체
struct DS_Vertex
{
	Vector3			Position;		// Vector3; 3차원 좌표
	Vector2			PositionUV;		// Vector2; 2차원 UV좌표
	Vector4			Color;			// Vector4; RGBA
};

//// Material용 구조체
//// 코드개선: 데이터 정렬(16바이트 단위) 및 SIMD를 고려한 최적화 포함
struct DS_MaterialConstant
{
	UINT				SDK_XM_UINT_Constant_s[4];						// 16 bytes (4 * 4); 0 -> TextureWidth, 1 -> TextureHeight
	FLOAT				SDK_XM_FLOAT_Constant_s[4];						// 16 bytes (4 * 4)
	XMFLOAT2			SDK_XM_FLOAT2_Constant_s[4];					// 16 * 2 bytes (8 * 4);
	XMFLOAT4			SDK_XM_FLOAT4_Constant_s[4];					// 16 * 4 bytes (16 * 4); 0 -> Color(RGBA)
	XMFLOAT4X4			SDK_XM_FLOAT4X4_Constant_s[4];					// 16 * 16 bytes (64 * 4); 유의! XMMATRIX랑 구조방식이 다르므로 XMMATRIX는 절대 쓰지 말 것!; 단, SimpleMath.h에 정의된 Matrix 구조체는 XMFLOAT4X4를 타입디파인한 거라 문제가 없으나, SDK 통일성을 위해 XMFLOAT4X4로 쓴다.

	// 텍스처 정보
	// 유의! DS_MaterialConstant 구조체의 데이터 정렬 때문에 bool아닌 SDK인 BOOL을 썻다는 점을 잊지 말 것!
	BOOL				SDK_XM_BOOL_Texture_s[_TEXTURE_END];			// 16 * 2 bytes + 8 bytes (4 * 6); 텍스처 분류 전용; 바인딩 되어 있으면 true, 아니면 false
	UINT				SDK_XM_Padding_s[2];							// 8 bytes; 16비트 정렬을 위해 넣는 더미 데이터
};

//// Material용 구조체
//// 코드개선: 데이터 정렬(16바이트 단위) 및 SIMD를 고려한 최적화 포함
struct DS_Transform
{
	XMFLOAT4X4	SDK_XM_FLOAT4X4_WorldMatrix;					// 16 * 4 bytes (64); 월드 행렬
	XMFLOAT4X4	SDK_XM_FLOAT4X4_ViewMatrix;						// 16 * 4 bytes (64); 뷰 행렬

	XMFLOAT4X4	SDK_XM_FLOAT4X4_WorldViewMatrix;				// 16 * 4 bytes (64); 월드 + 뷰 행렬

	XMFLOAT4X4	SDK_XM_FLOAT4X4_ProjectionMatrix;				// 16 * 4 bytes (64); 프로젝션 행렬

	XMFLOAT4X4	SDK_XM_FLOAT4X4_WorldViewProjectionMatrix;		// 16 * 4 bytes (64); 월드 + 뷰 + 프로젝션 행렬
};

extern DS_Transform G_DS_TransformVariable;

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