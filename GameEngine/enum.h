#pragma once

// DirectX
//// Buffer
enum E_CONSTANTBUFFER_TYPE
{
	// 향후, 사용할 레지스터를 정하는 것이 좋을 듯.
	// 상수버퍼이므로 b 레지스터를 사용
	_CONSTANTBUFFER_TRANSFORM,					// b0
	_CONSTANTBUFFER_MATERIAL,					// b1
	_CONSTANTBUFFER_GLOBAL,					// b2

	_CONSTANTBUFFER_END,
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
	_COMPONENT_MESH_RENDER,				// 가장 기본적인 RenderComponent
	_COMPONENT_SPRITE_RENDER,				// Sprite 하나 렌더링하는 컴포넌트
	_COMPONENT_FLIPBOOK_RENDER,			// Flipbook 재생 컴포넌트
	_COMPONENT_TILE_RENDER,				// 타일맵 렌더링
	_COMPONENT_PARTICLE_RENDER,			// 입자 렌더링

	_COMPONENT_END,

	_COMPONENT_SCRIPT,					// 대본, 역할, 컨텐츠
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