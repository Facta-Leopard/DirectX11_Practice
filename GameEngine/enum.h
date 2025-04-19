#pragma once

// OverHead를 줄이기 위해, enum class를 쓰지 않음
// 대신, 중복 문제를 줄이기 위해 '_'를 접미사로 사용하고,
// 무조건 대문자를 사용하며
// 단어별로 '_'로 끊는 것으로 정함

// DirectX
// Component형식으로 분류했던 방식으로, Buffer를 분류하는 것도 나쁘지 않을 듯
//// Buffer; 버퍼타입으로 바인드될 레지스터 숫자 대체
enum E_CONSTANTBUFFER_TYPE
{
	// 향후, 사용할 레지스터를 정하는 것이 좋을 듯.
	// 상수버퍼이므로 b 레지스터를 사용
	_CONSTANTBUFFER_TRANSFORM,					// b0: register 번호
	_CONSTANTBUFFER_MATERIAL,					// b1
	_CONSTANTBUFFER_GLOBAL,						// b2

	_CONSTANTBUFFER_END,
};

enum E_STRUCTUREDBUFFER_TYPE
{
	// 향후, 사용할 레지스터를 정하는 것이 좋을 듯.
	// 상수버퍼이므로 b 레지스터를 사용
	_STRUCTUREDBUFFER_SHADERRESOURCEVIEW_ONLY,					 // tRegister
	_STRUCTUREDBUFFER_UNORDEREDACCESSVIEW_ADDED,				 // uRegister

	_STRUCTUREDBUFFER_UNORDEREDACCESSVIEW_ONLY,					 // 결과를 그래픽 파이프라인에서 보여주는 쉐이더리소스뷰가 꼭 필요한 게임업계에서 안 쓰고, 그럴 필요가 없는 실험용에서만 자주 씀; 유의! 게임엔진이 아닌 다른 용도로만 쓸 거면, 이 부분은 사용하지 말 것이며, 만약 다른 용도로 전용한다면 C_StructuredBuffer::MF_Create_StructuredBuffer() 내 분기문 등을 전체적으로 수정할 것!

	_STRUCTUREDBUFFER_END,
};

// DirectX_Rendering Pipeline
//// Vertex
enum E_PROJECTION_TYPE
{
	_PROJECTION_ORTHOGRAPHIC,				// 직교투영
	_PROJECTION_PERSPECTIVE,				// 원근투영
};


//// Rasterizer
enum E_RASTERIZER_TYPE
{
	_RASTERIZER_CULL_BACK,					// cull_ccw, 뒷면(반시계 순서) 컬링
	_RASTERIZER_CULL_FRONT,				// cull_cw
	_RASTERIZER_CULL_NONE,					// 컬링하지 않음
	_RASTERIZER_WIRE_FRAME,				// 컬링하지 않으나, edge는 보임

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
	_DEPTHSTENCIL_LESS,						// 깊이판정 : 더 작아야 통과, 깊이 기록 O
	_DEPTHSTENCIL_LESS_EQUAL,				// 깊이판정 : 더 작아야 같으면 통과, 깊이 기록 O

	_DEPTHSTENCIL_GREATER,					// 깊이판정 : 더 멀어야 통과, 깊이 기록 0

	_DEPTHSTENCIL_NO_WRITE,					// 깊이판정 : 더 작아야 통과(LESS), 깊이 기록 X
	_DEPTHSTENCIL_NO_TEST_NO_WIRITE,		// 깊이판정 항상 성공(검사X), 깊이 기록 X

	_DEPTHSTENCIL_END,
};

//// OutputMerger
enum E_DOMAIN_TYPE
{
	_DOMAIN_QPAQUE,				// 불투명
	_DOMAIN_MASKED,				// 불투명 + 완전 투명
	_DOMAIN_TRANSPARENT,		// 반투명 + 투명	
	_DOMAIN_POSTPROCESS,		// 후처리

	_DOMAIN_DEBUG,				// 디버그 렌더링
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
enum E_STAGE_NUMBER					// 향후, 스테이지 타입으로 바꾸는 게 더 가독성이 나을지 고민해봐야 할 듯			
{
	_STAGE_0,						// 향후, 실행시 초기화면으로 정의예정
	_STAGE_1,						// 향후, 메인메뉴로 정의예정
	_STAGE_2,						// 향후, 케릭터 선택메뉴로 정의예정
	_STAGE_3,						// 향후, 게임플레이하는 스테이지로 정의예정
	_STAGE_4,						// 향후, 종료화면으로 정의예정

	_STAGE_END,						// 인덱스용
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
	_GROUP_PLAYER,					// 향후, RTS 장르에서도 적용할 수 있도록, 좀 더 세분하는 것이 어떨지 생각해보자.
	_GROUP_PLAYER_MISSILE,

	_GROUP_ENEMY,					// 향후, ENEMY가 아닌 PLAYER를 세분해서 각 자 적대화 하는 형식이 어떻지 생각해보자.
	_GROUP_ENEMY_MISSOLE,

	_GROUP_OBJECT_INTERACTABLE,
	_GROUP_OBJECT_UNINTERACTABLE,

	_GROUP_END,

	_GROUP_NONE,						// 유의! C_Object 내부 M_GroupIndex 복사관련; 향후, 문제 발생시에 void C_Group::MF_Attach_ObjectToParentObject(C_Object* _Object, bool _IsChildTogether) 내부의 if (nullptr == T_Object->MF_Get_ParentObject() || _IsChildTogether || T_Object->MF_Get_GroupType() == _GROUP_END) 부분을 확인할 것
};

enum E_OBJECT_TYPE					// 유의! 충돌검사 계층적 검사로 코드 개선하기 위한 enum으로 충돌체와 관련이 있음; 향후, 충돌 체크방식을 개선한 이 방식이 더 효율적인지 확인해보는 것이 좋겠다.
{
	_OBJECT_CHARACTER,				// 향후, 몸통이나 이런 종류로 세분하는 것이 좋을 듯.
	_OBJECT_WEAPON,					// 향후, 별도로 종류를 세분하는 것은 어떨지 생각해보는 것이 좋겠다. 밀리와 레인지, 또는 직접 총, 활, 칼, 창 등의 구분이라던가..
	_OBJECT_ARMOR,					// 향후, 방패나 경갑, 중갑 등 분류하는 것은 어떨지 생각해보는 것이 좋겠다.
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
	_COMPONENT_MESH_RENDER,				// 가장 기본적인 RenderComponent
	_COMPONENT_SPRITE_RENDER,			// Sprite 하나 렌더링하는 컴포넌트
	_COMPONENT_FLIPBOOK_RENDER,			// Flipbook 재생 컴포넌트
	_COMPONENT_TILE_RENDER,				// 타일맵 렌더링
	_COMPONENT_PARTICLE_RENDER,			// 입자 렌더링

	_COMPONENT_END,

	// Script Component
	_COMPONENT_SCRIPT,					// 별도 타입 세분화, E_SCRIPT_TYPE 참조

	// Render Component
	_COMPONENT_RENDER,					// 자기자신 반환 추상함수 방어코드용
};

////// about Collider Type
enum E_COLLIDER_TYPE
{
	_COLLIDER_2D_SIDESCROLL_,			// Front(Z축 무효); OBB는 기본적으로 사용하는 것으로 함
	_COLLIDER_2D_TOPVEIW,				// Up(Y축 무효); OBB는 기본적으로 사용하는 것으로 함
	_COLLIDER_2D_ISOMETRICVIEW,			// Up(Y축 무효); OBB는 기본적으로 사용하는 것으로 함; _COLLIDER_2D_TOPVEIW와 동일;
	_COLLIDER_3D_SAT_ON,				// 축 무효없음; S.A.T.(Saperating Axis Theorem) 무조건 적용
	_COLLIDER_3D_SAT_OFF,				// 축 무효없음; S.A.T.(Saperating Axis Theorem) 무조건 미적용

	_COLLIDER_TYPE_END,					// 인덱스 리딩에러 방지용
};

////// about Script
enum E_SCRIPT_TYPE										// 유의! enum 변동 있을 시, template <typename T_Template> T_Template* MF_Get_ComponentByReturnType() 템플릿 특수화 추가 필요
{
	_SCRIPT_RIGID,						// 강체관련
	_SCRIPT_STATE,						// 상태관련
	_SCRIPT_MOVE,						// 이동관련
	_SCRIPT_NPC,						// 반응관련

	_SCRIPT_CAMERA,						// 카메라관련

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
	_LIGHTING_DIRECTIONAL,			// 방향성 광원, 전역 (태양, 달)
	_LIGHTING_POINT,				// 점광원, 전구, 전등, 횃불
	_LIGHTING_SPOT,				// 스포트라이트, 손전등
};


//// about Direction
enum E_DIRECTION_TYPE
{
	_DIRECTION_RIGHT,			// X-Axis
	_DIRECTION_UP,				// Y-Axis
	_DIRECTION_FRONT,			// Z-Axis

	_DIRECTION_END,
};