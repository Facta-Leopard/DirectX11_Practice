#pragma once

#include "pch.h"
#include "component.h"

// inline에 대한 잘못된 인식을 개선했음
// inline은 .cpp없이도 링킹할 수 있게 하는 것과 컴파일러 최적화의 두 종류가 있었음
// 이 함수는 .cpp 없이 쓸 수 있도록 하는 inline 함수
inline bool GF_Toggle(bool _input)
{
	if (_input)
	{
		return false;
	}
	else
	{
		return true;
	}
}

// Component 분류를 위한 Switch문
inline C_Transform GF_ComponentTypeCheck(C_Component* _Component)
{
	C_Component* T_Component = _Component;

	E_COMPONENT_TYPE T_ComponentType = T_Component->MF_GetComponentType();

	switch (T_ComponentType)
	{
	case _COMPONENT_TRANSFORM:
		break;
	case _COMPONENT_COLLIDER_2D:
		break;
	case _COMPONENT_LIGHT_2D:
		break;
	case _COMPONENT_CAMERA:
		break;
	case _COMPONENT_MESH_RENDER:
		break;
	case _COMPONENT_SPRITE_RENDER:
		break;
	case _COMPONENT_FLIPBOOK_RENDER:
		break;
	case _COMPONENT_TILE_RENDER:
		break;
	case _COMPONENT_PARTICLE_RENDER:
		break;
	case _COMPONENT_END:
	case _COMPONENT_SCRIPT:
	default:
		break;
	}
}
