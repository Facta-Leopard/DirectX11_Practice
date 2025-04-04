#pragma once

// DirectX
//// Buffer
enum E_CONSTANTBUFFER_TYPE
{
	// ����, ����� �������͸� ���ϴ� ���� ���� ��.
	// ��������̹Ƿ� b �������͸� ���
	_CONSTANTBUFFER_TRANSFORM,					// b0
	_CONSTANTBUFFER_MATERIAL,					// b1
	_CONSTANTBUFFER_GLOBAL,					// b2

	_CONSTANTBUFFER_END,
};




// DirectX_Rendering Pipeline
//// Vertex
enum E_PROJECTION_TYPE
{
	_PROJECTION_ORTHOGRAPHIC,				// ��������
	_PROJECTION_PERSPECTIVE,				// ��������
};


//// Rasterizer
enum E_RASTERIZER_TYPE
{
	_RASTERIZER_CULL_BACK,					// cull_ccw, �޸�(�ݽð� ����) �ø�
	_RASTERIZER_CULL_FRONT,				// cull_cw
	_RASTERIZER_CULL_NONE,					// �ø����� ����
	_RASTERIZER_WIRE_FRAME,				// �ø����� ������, edge�� ����

	_RASTERIZER_END,
};


//// Pixel
enum E_BLEND_STATE
{
	_BLEND_DEFAULT,					// Src : 1, Dst : 0
	_BLEND_ALPHABLEND,				// Src : A, Dst : (1 - A)

	_BLEND_END,
};


//// Sampler
enum E_SAMPLER_TYPE
{

};


//// DepthStencil State
enum E_DEPTHSTENCIL_STATE
{
	_DEPTHSTENCIL_LESS,						// �������� : �� �۾ƾ� ���, ���� ��� O
	_DEPTHSTENCIL_LESS_EQUAL,				// �������� : �� �۾ƾ� ������ ���, ���� ��� O

	_DEPTHSTENCIL_GREATER,					// �������� : �� �־�� ���, ���� ��� 0

	_DEPTHSTENCIL_NO_WRITE,					// �������� : �� �۾ƾ� ���(LESS), ���� ��� X
	_DEPTHSTENCIL_NO_TEST_NO_WIRITE,		// �������� �׻� ����(�˻�X), ���� ��� X

	_DEPTHSTENCIL_END,
};

//// OutputMerger
enum E_DOMAIN_TYPE
{
	_DOMAIN_QPAQUE,				// ������
	_DOMAIN_MASKED,				// ������ + ���� ����
	_DOMAIN_TRANSPARENT,		// ������ + ����	
	_DOMAIN_POSTPROCESS,		// ��ó��

	_DOMAIN_DEBUG,				// ����� ������
};




// In Program
//// about Progress
enum E_TASK_TYPE
{
	_TASK_CREATE_OBJECT,
	_TASK_DELETE_OBJECT,

	_TASK_ADD_CHILD_OBJECT,

	_TASK_CHANGE_STAGE,
	_TASK_CHANGE_STAGE_STATE,

	_TASK_DELETE_RESOURCE,
};


//// about Stage
enum E_STAGE_STATE
{
	_STAGE_PLAY,
	_STAGE_PAUSE,
	_STAGE_STOP,
};

//// about Resourece
enum E_RESOURCE_TYPE
{
	_RESOURCE_MESH,
	_RESOURCE_MESHDATA,
	_RESOURCE_TEXTURE,
	_RESOURCE_MATERIAL,
	_RESOURCE_PREFAB,
	_RESOURCE_SOUND,
	_GRAPHIC_SHADER,
	_COMPUTE_SHADER,
	_RESOURCE_SPRITE,
	_RESOURCE_FLIPBOOK,

	_RESOURCE_RESOURCE_END,
};

enum E_TEXTURE_NUMBER
{
	_TEXTURE_0,
	_TEXTURE_1,
	_TEXTURE_2,
	_TEXTURE_3,
	_TEXTURE_4,
	_TEXTURE_5,

	_TEXTURE_END,
};


//// about Component
enum E_COMPONENT_TYPE
{
	_COMPONENT_TRANSFORM,
	_COMPONENT_COLLIDER_2D,
	_COMPONENT_LIGHTING_2D,
	_COMPONENT_CAMERA,

	// Rendering Component
	_COMPONENT_MESH_RENDER,				// ���� �⺻���� RenderComponent
	_COMPONENT_SPRITE_RENDER,				// Sprite �ϳ� �������ϴ� ������Ʈ
	_COMPONENT_FLIPBOOK_RENDER,			// Flipbook ��� ������Ʈ
	_COMPONENT_TILE_RENDER,				// Ÿ�ϸ� ������
	_COMPONENT_PARTICLE_RENDER,			// ���� ������

	_COMPONENT_END,

	_COMPONENT_SCRIPT,					// �뺻, ����, ������
};


//// about Debug Rendering
////// about Rendering Shape
enum E_DEBUGRENDER_TYPE
{
	_DEBUGRENDER_RECTANGLE,
	_DEBUGRENDER_CIRCLE,
	_DEBUGRENDER_LINE,
};


////// about Lighing
enum E_LIGHTING_TYPE
{
	_LIGHTING_DIRECTIONAL,			// ���⼺ ����, ���� (�¾�, ��)
	_LIGHTING_POINT,				// ������, ����, ����, ȶ��
	_LIGHTING_SPOT,				// ����Ʈ����Ʈ, ������
};


//// about Direction
enum E_DIRECTION_TYPE
{
	_DIRECTION_RIGHT,			// X-Axis
	_DIRECTION_UP,				// Y-Axis
	_DIRECTION_FRONT,			// Z-Axis

	_DIRECTION_END,
};