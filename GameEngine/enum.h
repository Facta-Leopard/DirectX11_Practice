#pragma once

// OverHead�� ���̱� ����, enum class�� ���� ����
// ���, �ߺ� ������ ���̱� ���� '_'�� ���̻�� ����ϰ�,
// ������ �빮�ڸ� ����ϸ�
// �ܾ�� '_'�� ���� ������ ����

// DirectX
// Component�������� �з��ߴ� �������, Buffer�� �з��ϴ� �͵� ������ ���� ��
//// Buffer; ����Ÿ������ ���ε�� �������� ���� ��ü
enum E_CONSTANTBUFFER_TYPE
{
	// ����, ����� �������͸� ���ϴ� ���� ���� ��.
	// ��������̹Ƿ� b �������͸� ���
	_CONSTANTBUFFER_TRANSFORM,					// b0: register ��ȣ
	_CONSTANTBUFFER_MATERIAL,					// b1
	_CONSTANTBUFFER_GLOBAL,						// b2

	_CONSTANTBUFFER_END,
};

enum E_STRUCTUREDBUFFER_TYPE
{
	// ����, ����� �������͸� ���ϴ� ���� ���� ��.
	// ��������̹Ƿ� b �������͸� ���
	_STRUCTUREDBUFFER_SHADERRESOURCEVIEW_ONLY,					 // tRegister
	_STRUCTUREDBUFFER_UNORDEREDACCESSVIEW_ADDED,				 // uRegister

	_STRUCTUREDBUFFER_UNORDEREDACCESSVIEW_ONLY,					 // ����� �׷��� ���������ο��� �����ִ� ���̴����ҽ��䰡 �� �ʿ��� ���Ӿ��迡�� �� ����, �׷� �ʿ䰡 ���� ����뿡���� ���� ��; ����! ���ӿ����� �ƴ� �ٸ� �뵵�θ� �� �Ÿ�, �� �κ��� ������� �� ���̸�, ���� �ٸ� �뵵�� �����Ѵٸ� C_StructuredBuffer::MF_Create_StructuredBuffer() �� �б⹮ ���� ��ü������ ������ ��!

	_STRUCTUREDBUFFER_END,
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
//// about Key
enum E_KEY_TYPE
{
	_KEY_Q, _KEY_W, _KEY_E, _KEY_R, _KEY_T, _KEY_Y,
	_KEY_A, _KEY_S, _KEY_D, _KEY_F, _KEY_G, _KEY_H,
	_KEY_Z, _KEY_X, _KEY_C, _KEY_V, _KEY_B, _KEY_N, _KEY_M,

	_KEY_ENTER,
	_KEY_ESC,
	_KEY_LSHIFT,
	_KEY_ALT,
	_KEY_CTRL,
	_KEY_SPACE,

	_KEY_UP, _KEY_DOWN, _KEY_LEFT, _KEY_RIGHT,

	_KEY_NUM0,
	_KEY_NUM1,
	_KEY_NUM2,
	_KEY_NUM3,
	_KEY_NUM4,
	_KEY_NUM5,
	_KEY_NUM6,
	_KEY_NUM7,
	_KEY_NUM8,
	_KEY_NUM9,

	_KEY_LBTN,
	_KEY_RBTN,

	_KEY_END,
};
 
enum E_KEY_STATE
{
	_KEY_NONE,
	_KEY_TAP,
	_KEY_PRESSED,
	_KEY_RELEASED,
};


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
////// about Stage Number
enum E_STAGE_NUMBER					// ����, �������� Ÿ������ �ٲٴ� �� �� �������� ������ ����غ��� �� ��			
{
	_STAGE_0,						// ����, ����� �ʱ�ȭ������ ���ǿ���
	_STAGE_1,						// ����, ���θ޴��� ���ǿ���
	_STAGE_2,						// ����, �ɸ��� ���ø޴��� ���ǿ���
	_STAGE_3,						// ����, �����÷����ϴ� ���������� ���ǿ���
	_STAGE_4,						// ����, ����ȭ������ ���ǿ���

	_STAGE_END,						// �ε�����
};


////// about Stage State
enum E_STAGE_STATE
{
	_STAGE_PLAY,
	_STAGE_PAUSE,
	_STAGE_STOP,
};


//// about Group
enum E_GROUP_INDEX
{
	_GROUP_PLAYER,					// ����, RTS �帣������ ������ �� �ֵ���, �� �� �����ϴ� ���� ��� �����غ���.
	_GROUP_PLAYER_MISSILE,

	_GROUP_ENEMY,					// ����, ENEMY�� �ƴ� PLAYER�� �����ؼ� �� �� ����ȭ �ϴ� ������ ��� �����غ���.
	_GROUP_ENEMY_MISSOLE,

	_GROUP_OBJECT_INTERACTABLE,
	_GROUP_OBJECT_UNINTERACTABLE,

	_GROUP_END,

	_GROUP_NONE,						// ����! C_Object ���� M_GroupIndex �������; ����, ���� �߻��ÿ� void C_Group::MF_Attach_ObjectToParentObject(C_Object* _Object, bool _IsChildTogether) ������ if (nullptr == T_Object->MF_Get_ParentObject() || _IsChildTogether || T_Object->MF_Get_GroupType() == _GROUP_END) �κ��� Ȯ���� ��
};

enum E_OBJECT_TYPE					// ����! �浹�˻� ������ �˻�� �ڵ� �����ϱ� ���� enum���� �浹ü�� ������ ����; ����, �浹 üũ����� ������ �� ����� �� ȿ�������� Ȯ���غ��� ���� ���ڴ�.
{
	_OBJECT_CHARACTER,				// ����, �����̳� �̷� ������ �����ϴ� ���� ���� ��.
	_OBJECT_WEAPON,					// ����, ������ ������ �����ϴ� ���� ��� �����غ��� ���� ���ڴ�. �и��� ������, �Ǵ� ���� ��, Ȱ, Į, â ���� �����̶����..
	_OBJECT_ARMOR,					// ����, ���г� �氩, �߰� �� �з��ϴ� ���� ��� �����غ��� ���� ���ڴ�.
	_OBJECT_GENERIC,

	_OBJECT_END,


};

//// about Component
enum E_COMPONENT_TYPE
{
	_COMPONENT_TRANSFORM,
	_COMPONENT_COLLIDER2D,
	_COMPONENT_STATE,
	_COMPONENT_LIGHT2D,

	_COMPONENT_CAMERA,

	// Render Component
	_COMPONENT_MESH_RENDER,				// ���� �⺻���� RenderComponent
	_COMPONENT_SPRITE_RENDER,			// Sprite �ϳ� �������ϴ� ������Ʈ
	_COMPONENT_FLIPBOOK_RENDER,			// Flipbook ��� ������Ʈ
	_COMPONENT_TILE_RENDER,				// Ÿ�ϸ� ������
	_COMPONENT_PARTICLE_RENDER,			// ���� ������

	_COMPONENT_END,

	// Script Component
	_COMPONENT_SCRIPT,					// ���� Ÿ�� ����ȭ, E_SCRIPT_TYPE ����

	// Render Component
	_COMPONENT_RENDER,					// �ڱ��ڽ� ��ȯ �߻��Լ� ����ڵ��
};

////// about Collider Type
enum E_COLLIDER_TYPE
{
	_COLLIDER_2D_SIDESCROLL_,			// Front(Z�� ��ȿ); OBB�� �⺻������ ����ϴ� ������ ��
	_COLLIDER_2D_TOPVEIW,				// Up(Y�� ��ȿ); OBB�� �⺻������ ����ϴ� ������ ��
	_COLLIDER_2D_ISOMETRICVIEW,			// Up(Y�� ��ȿ); OBB�� �⺻������ ����ϴ� ������ ��; _COLLIDER_2D_TOPVEIW�� ����;
	_COLLIDER_3D_SAT_ON,				// �� ��ȿ����; S.A.T.(Saperating Axis Theorem) ������ ����
	_COLLIDER_3D_SAT_OFF,				// �� ��ȿ����; S.A.T.(Saperating Axis Theorem) ������ ������

	_COLLIDER_TYPE_END,					// �ε��� �������� ������
};

////// about Script
enum E_SCRIPT_TYPE										// ����! enum ���� ���� ��, template <typename T_Template> T_Template* MF_Get_ComponentByReturnType() ���ø� Ư��ȭ �߰� �ʿ�
{
	_SCRIPT_RIGID,						// ��ü����
	_SCRIPT_STATE,						// ���°���
	_SCRIPT_MOVE,						// �̵�����
	_SCRIPT_NPC,						// ��������

	_SCRIPT_CAMERA,						// ī�޶����

	_SCRIPT_END,
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