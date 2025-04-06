#pragma once

#include "pch.h"
#include "component.h"

// inline�� ���� �߸��� �ν��� ��������
// inline�� .cpp���̵� ��ŷ�� �� �ְ� �ϴ� �Ͱ� �����Ϸ� ����ȭ�� �� ������ �־���
// �� �Լ��� .cpp ���� �� �� �ֵ��� �ϴ� inline �Լ�
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

// Component �з��� ���� Switch��
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
