#pragma once

#include "DirectXMath.h"

#include "define.h"

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

// Bind ���� ����ü
//// Vertex�� ����ü
struct DS_Vertex
{
	Vector3			Position;		// Vector3; 3���� ��ǥ
	Vector2			PositionUV;		// Vector2; 2���� UV��ǥ
	Vector4			Color;			// Vector4; RGBA
};

//// Material�� ����ü
//// �ڵ尳��: ������ ����(16����Ʈ ����) �� SIMD�� ����� ����ȭ ����
struct DS_MaterialConstant
{
	UINT				SDK_XM_UINT_Constant_s[4];						// 16 bytes (4 * 4); 0 -> TextureWidth, 1 -> TextureHeight
	FLOAT				SDK_XM_FLOAT_Constant_s[4];						// 16 bytes (4 * 4)
	XMFLOAT2			SDK_XM_FLOAT2_Constant_s[4];					// 16 * 2 bytes (8 * 4);
	XMFLOAT4			SDK_XM_FLOAT4_Constant_s[4];					// 16 * 4 bytes (16 * 4); 0 -> Color(RGBA)
	XMFLOAT4X4			SDK_XM_FLOAT4X4_Constant_s[4];					// 16 * 16 bytes (64 * 4); ����! XMMATRIX�� ��������� �ٸ��Ƿ� XMMATRIX�� ���� ���� �� ��!; ��, SimpleMath.h�� ���ǵ� Matrix ����ü�� XMFLOAT4X4�� Ÿ�Ե������� �Ŷ� ������ ������, SDK ���ϼ��� ���� XMFLOAT4X4�� ����.

	// �ؽ�ó ����
	// ����! DS_MaterialConstant ����ü�� ������ ���� ������ bool�ƴ� SDK�� BOOL�� ���ٴ� ���� ���� �� ��!
	BOOL				SDK_XM_BOOL_Texture_s[_TEXTURE_END];			// 16 * 2 bytes + 8 bytes (4 * 6); �ؽ�ó �з� ����; ���ε� �Ǿ� ������ true, �ƴϸ� false
	UINT				SDK_XM_Padding_s[2];							// 8 bytes; 16��Ʈ ������ ���� �ִ� ���� ������
};

//// Material�� ����ü
//// �ڵ尳��: ������ ����(16����Ʈ ����) �� SIMD�� ����� ����ȭ ����
struct DS_Transform
{
	XMFLOAT4X4	SDK_XM_FLOAT4X4_WorldMatrix;					// 16 * 4 bytes (64); ���� ���
	XMFLOAT4X4	SDK_XM_FLOAT4X4_ViewMatrix;						// 16 * 4 bytes (64); �� ���

	XMFLOAT4X4	SDK_XM_FLOAT4X4_WorldViewMatrix;				// 16 * 4 bytes (64); ���� + �� ���

	XMFLOAT4X4	SDK_XM_FLOAT4X4_ProjectionMatrix;				// 16 * 4 bytes (64); �������� ���

	XMFLOAT4X4	SDK_XM_FLOAT4X4_WorldViewProjectionMatrix;		// 16 * 4 bytes (64); ���� + �� + �������� ���
};


// FL_IMAGE_PACKER ���; ���� ���� ���̺귯��
//// FL_ResourceImageDesc ���� ���п� �÷���
enum FL_E_IMAGETYPE
{
	_IMAGETYPE_PNG,				// PNG ���Ͽ�
	_IMAGETYPE_JPG,				// JPG ���Ͽ�
	_IMAGETYPE_JPEG,			// JPEG ���Ͽ�
	_IMAGETYPE_BMP,				// BMP ���Ͽ�

	_IMAGETYPE_END,
};

//// C.O.M.(Component Object Model) ���� ������ ���� ��Ÿ������ ����ü
struct FL_DS_ResourceImageDesc
{
	// ���ҽ��� �����ϰų�, ���ҽ��� �ִ� ���丮 �ּ�; ����� ��쿡�� �⺻������ ���� ���丮 + (\Resource) ���丮 �ּҸ� ������� ��
	wstring						wstring_Path = L"EMPTY";

	// ����� �����ϱ� ���� ���п� �÷��׷� ���; ����� ��쿡�� PNG�� ������� ��
	FL_E_IMAGETYPE				E_ImageType = _IMAGETYPE_PNG;
};

//// ��ũ��ġ �̹����� ȯ���� ����� ���� ����ü
struct FL_DS_ImageEntry
{
	size_t				SDK_M_Width;				// ��������
	size_t				SDK_M_Height;				// ��������
	DXGI_FORMAT			DX_M_ImageFormat;			// �̹��� ��������
	size_t				SDK_M_RowPitch;				// �� �ٴ� �ȼ��� �����ϴ� ũ��
	size_t				SDK_M_SlicePitch;			// ��ü �̹��� ũ��(SDK_M_RowPitch * SDK_M_Height)
	size_t				SDK_M_OffsetInBlob;			// Offset ����
};

//// ���ҽ� ��ŷ���� ����ü
struct FL_DS_CPU_Image
{
	TexMetadata					M_MetaData;			// �̹��� ������ ���� �ִ� ��Ÿ������; �Ҹ� �� ������ �������; DirectX ����
	vector<FL_DS_ImageEntry>       STL_M_Entry;		// ��ũ��ġ �̹����� ȯ���� ����� ������
	vector<uint8_t>             M_PixelBlob;		// �̹����� ���� ��ü����(1���� ����)��, ��� ������ �� �ٷ� ���
};

//// ���ҽ� �̹�����Ʈ
struct FL_DS_ImageSet
{
	FL_DS_CPU_Image					M_CPUImage;
	FL_DS_ResourceImageDesc			M_Desc;
};




// ��������

extern DS_Transform G_DS_TransformVariable;






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