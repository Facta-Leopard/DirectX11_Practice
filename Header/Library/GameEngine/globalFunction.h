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

//향후, 구현예정이었으나 방향 바꿈; C_Component의 다형성을 이용해 자기자신 반환 함수 구현; C_Component::MF_Get_Myself()
//// Component 분류를 위한 Switch문
//{
//	inline C_Transform GF_ComponentTypeCheck(C_Component * _Component)
//	{
//		if (nullptr == _Component)		// 방어코드
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
//		if (nullptr == _Component)			// 방어코드
//		{
//			POPUP_DEBUG(L"C_Component Is nullptr", L"in C_Transform* GF_ConvertComponentToTransform(), nullptr == _Component")
//		}
//		return (C_Transform*)_Component;
//	}
//
//	C_Collider2D* GF_ConvertComponentToCollider2D(C_Component * _Component)
//	{
//		if (nullptr == _Component)			// 방어코드
//		{
//			POPUP_DEBUG(L"C_Component Is nullptr", L"in C_Transform* GF_ConvertComponentToCollider2D(), nullptr == _Component")
//		}
//		return (C_Collider2D*)_Component;
//	}
//
//	C_Light2D* GF_ConvertComponentToLight2D(C_Component * _Component)
//	{
//		if (nullptr == _Component)			// 방어코드
//		{
//			POPUP_DEBUG(L"C_Component Is nullptr", L"in C_Transform* GF_ConvertComponentToLight2D(), nullptr == _Component")
//		}
//		return (C_Light2D*)_Component;
//	}
//
//	C_CameraComponent* GF_ConvertComponentToCameraComponent(C_Component * _Component)
//	{
//		if (nullptr == _Component)			// 방어코드
//		{
//			POPUP_DEBUG(L"C_Component Is nullptr", L"in C_Transform* GF_ConvertComponentToCameraComponent(), nullptr == _Component")
//		}
//		return (C_CameraComponent*)_Component;
//	}
//
//	C_MeshRender* GF_ConvertComponentToMeshRender(C_Component * _Component)
//	{
//		if (nullptr == _Component)			// 방어코드
//		{
//			POPUP_DEBUG(L"C_Component Is nullptr", L"in C_Transform* GF_ConvertComponentToMeshRender(), nullptr == _Component")
//		}
//		return (C_MeshRender*)_Component;
//	}
//
//	C_SpriteRender* GF_ConvertComponentToSpriteRender(C_Component * _Component)
//	{
//		if (nullptr == _Component)			// 방어코드
//		{
//			POPUP_DEBUG(L"C_Component Is nullptr", L"in C_Transform* GF_ConvertComponentToSpriteRender(), nullptr == _Component")
//		}
//		return (C_SpriteRender*)_Component;
//	}
//
//	C_FlipbookRender* GF_ConvertComponentToFlipbookRender(C_Component * _Component)
//	{
//		if (nullptr == _Component)			// 방어코드
//		{
//			POPUP_DEBUG(L"C_Component Is nullptr", L"in C_Transform* GF_ConvertComponentToFlipbookRender(), nullptr == _Component")
//		}
//		return (C_FlipbookRender*)_Component;
//	}
//
//	C_TileRender* GF_ConvertComponentToTileRender(C_Component * _Component)
//	{
//		if (nullptr == _Component)			// 방어코드
//		{
//			POPUP_DEBUG(L"C_Component Is nullptr", L"in C_Transform* GF_ConvertComponentToTileRender(), nullptr == _Component")
//		}
//		return (C_TileRender*)_Component;
//	}
//
//	C_ParticleRender* GF_ConvertComponentToParticleRender(C_Component * _Component)
//	{
//		if (nullptr == _Component)			// 방어코드
//		{
//			POPUP_DEBUG(L"C_Component Is nullptr", L"in C_Transform* GF_ConvertComponentToParticleRender(), nullptr == _Component")
//		}
//		return (C_ParticleRender*)_Component;
//	}
//}




















