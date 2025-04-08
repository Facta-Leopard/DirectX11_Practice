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

//����, ���������̾����� ���� �ٲ�; C_Component�� �������� �̿��� �ڱ��ڽ� ��ȯ �Լ� ����; C_Component::MF_Get_Myself()
//// Component �з��� ���� Switch��
//{
//	inline C_Transform GF_ComponentTypeCheck(C_Component * _Component)
//	{
//		if (nullptr == _Component)		// ����ڵ�
//		{
//			POPUP_DEBUG(L"C_Component IS nullptr", L"in inline C_Transform GF_ComponentTypeCheck(), nullptr == _Component")
//				return;
//		}
//		C_Component* T_Component = _Component;
//
//		E_COMPONENT_TYPE T_ComponentType = T_Component->MF_Get_ComponentType();
//
//		switch (T_ComponentType)
//		{
//		case _COMPONENT_TRANSFORM:
//			break;
//		case _COMPONENT_COLLIDER_2D:
//			break;
//		case _COMPONENT_LIGHT_2D:
//			break;
//		case _COMPONENT_CAMERA:
//			break;
//		case _COMPONENT_MESH_RENDER:
//			break;
//		case _COMPONENT_SPRITE_RENDER:
//			break;
//		case _COMPONENT_FLIPBOOK_RENDER:
//			break;
//		case _COMPONENT_TILE_RENDER:
//			break;
//		case _COMPONENT_PARTICLE_RENDER:
//			break;
//		case _COMPONENT_END:
//		case _COMPONENT_SCRIPT:
//		default:
//			break;
//		}
//	}
//
//	C_Transform* GF_ConvertComponentToTransform(C_Component * _Component)
//	{
//		if (nullptr == _Component)			// ����ڵ�
//		{
//			POPUP_DEBUG(L"C_Component Is nullptr", L"in C_Transform* GF_ConvertComponentToTransform(), nullptr == _Component")
//		}
//		return (C_Transform*)_Component;
//	}
//
//	C_Collider2D* GF_ConvertComponentToCollider2D(C_Component * _Component)
//	{
//		if (nullptr == _Component)			// ����ڵ�
//		{
//			POPUP_DEBUG(L"C_Component Is nullptr", L"in C_Transform* GF_ConvertComponentToCollider2D(), nullptr == _Component")
//		}
//		return (C_Collider2D*)_Component;
//	}
//
//	C_Light2D* GF_ConvertComponentToLight2D(C_Component * _Component)
//	{
//		if (nullptr == _Component)			// ����ڵ�
//		{
//			POPUP_DEBUG(L"C_Component Is nullptr", L"in C_Transform* GF_ConvertComponentToLight2D(), nullptr == _Component")
//		}
//		return (C_Light2D*)_Component;
//	}
//
//	C_CameraComponent* GF_ConvertComponentToCameraComponent(C_Component * _Component)
//	{
//		if (nullptr == _Component)			// ����ڵ�
//		{
//			POPUP_DEBUG(L"C_Component Is nullptr", L"in C_Transform* GF_ConvertComponentToCameraComponent(), nullptr == _Component")
//		}
//		return (C_CameraComponent*)_Component;
//	}
//
//	C_MeshRender* GF_ConvertComponentToMeshRender(C_Component * _Component)
//	{
//		if (nullptr == _Component)			// ����ڵ�
//		{
//			POPUP_DEBUG(L"C_Component Is nullptr", L"in C_Transform* GF_ConvertComponentToMeshRender(), nullptr == _Component")
//		}
//		return (C_MeshRender*)_Component;
//	}
//
//	C_SpriteRender* GF_ConvertComponentToSpriteRender(C_Component * _Component)
//	{
//		if (nullptr == _Component)			// ����ڵ�
//		{
//			POPUP_DEBUG(L"C_Component Is nullptr", L"in C_Transform* GF_ConvertComponentToSpriteRender(), nullptr == _Component")
//		}
//		return (C_SpriteRender*)_Component;
//	}
//
//	C_FlipbookRender* GF_ConvertComponentToFlipbookRender(C_Component * _Component)
//	{
//		if (nullptr == _Component)			// ����ڵ�
//		{
//			POPUP_DEBUG(L"C_Component Is nullptr", L"in C_Transform* GF_ConvertComponentToFlipbookRender(), nullptr == _Component")
//		}
//		return (C_FlipbookRender*)_Component;
//	}
//
//	C_TileRender* GF_ConvertComponentToTileRender(C_Component * _Component)
//	{
//		if (nullptr == _Component)			// ����ڵ�
//		{
//			POPUP_DEBUG(L"C_Component Is nullptr", L"in C_Transform* GF_ConvertComponentToTileRender(), nullptr == _Component")
//		}
//		return (C_TileRender*)_Component;
//	}
//
//	C_ParticleRender* GF_ConvertComponentToParticleRender(C_Component * _Component)
//	{
//		if (nullptr == _Component)			// ����ڵ�
//		{
//			POPUP_DEBUG(L"C_Component Is nullptr", L"in C_Transform* GF_ConvertComponentToParticleRender(), nullptr == _Component")
//		}
//		return (C_ParticleRender*)_Component;
//	}
//}




















