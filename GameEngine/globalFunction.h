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

// 매트릭스 관련 전역함수
// 전역으로 하면 오버헤드가 줄어드는 효과가 있다.
//// 매트릭스에서 벡터로 뽑아내는 용도의 전영 함수
//// 참조는 아직도 익숙하지 않다..
//// 리턴값은 Right, Up, Look 벡터 길이를 통해 추출한 스케일값 (Vec3_T_Scale)
//// 지역 변수 없이 직접 리턴 → RVO + inline 최적화 유도
//// MAT_M_Source는 스케일이 포함된 변환 행렬이어야 함
// 
//// NRVO 버전; inline 걸려있어도 컴파일러 최적화가 안될 수 있으므로 주석처리만 함 
//inline Vector3 SF_Extract_ScaleFromMatrix(const Matrix& _Matrix)
//{
//	Vector3 Vec3_T_Scale = {};
//
//	Vec3_T_Scale.x = sqrtf((_Matrix._11 * _Matrix._11) + (_Matrix._21 * _Matrix._21) + (_Matrix._31 * _Matrix._31));
//	Vec3_T_Scale.y = sqrtf((_Matrix._12 * _Matrix._12) + (_Matrix._22 * _Matrix._22) + (_Matrix._32 * _Matrix._32));
//	Vec3_T_Scale.z = sqrtf((_Matrix._13 * _Matrix._13) + (_Matrix._23 * _Matrix._13) + (_Matrix._33 * _Matrix._33));
//
//	return Vec3_T_Scale;
//}

//// RVO 버전
inline Vector3 SF_Get_ScaleVector3FromMatrix(const Matrix& _Matrix)
{
	return Vector3(
		sqrtf((_Matrix._11 * _Matrix._11) + (_Matrix._21 * _Matrix._21) + (_Matrix._31 * _Matrix._31)),
		sqrtf((_Matrix._12 * _Matrix._12) + (_Matrix._22 * _Matrix._22) + (_Matrix._32 * _Matrix._32)),
		sqrtf((_Matrix._13 * _Matrix._13) + (_Matrix._23 * _Matrix._13) + (_Matrix._33 * _Matrix._33))
	);
}

// 매트릭스에서 방향벡터 뽑아내기
inline Vector3 GF_Get_DirectionVector3FromMatrix(const Matrix& _Matrix, E_DIRECTION_TYPE _DIRECTIONTYPE)
{
	switch (_DIRECTIONTYPE)
	{
	case _DIRECTION_RIGHT:
		return (Vector3)(_Matrix._11, _Matrix._12, _Matrix._13);
		break;
	case _DIRECTION_UP:
		return (Vector3)(_Matrix._21, _Matrix._22, _Matrix._23);
		break;
	case _DIRECTION_FRONT:
		return (Vector3)(_Matrix._31, _Matrix._32, _Matrix._33);
		break;
	default:
		return (Vector3)(_Matrix._31, _Matrix._32, _Matrix._33);
		break;
	}
}


//// 매트릭스 스케일만 조정
//// 참조는 아직도 익숙하지 않다.
inline void GF_Set_ScaleToMatrix(Matrix& _Matrix, const Vector3& V_Scale)
{
	// X축 방향 벡터 (Right)
	_Matrix._11 *= V_Scale.x;
	_Matrix._12 *= V_Scale.x;
	_Matrix._13 *= V_Scale.x;

	// Y축 방향 벡터 (Up)
	_Matrix._21 *= V_Scale.y;
	_Matrix._22 *= V_Scale.y;
	_Matrix._23 *= V_Scale.y;

	// Z축 방향 벡터 (Look)
	_Matrix._31 *= V_Scale.z;
	_Matrix._32 *= V_Scale.z;
	_Matrix._33 *= V_Scale.z;

	// 유의! _41, _42, _43은 위치 값과 관련이 있어서 건드리면 대형사고 나니까 절대 조심
}

// Vector3 관련 전역함수
//// Vector3 값을 리버스한다.
//// NRVO 버전
//inline Vector3 GF_Apply_InverseVector(const Vector3& _Vector3)
//{
//	Vector3 Vec_T_Scale = {};
//
//	if (0.f == _Vector3.x)						// 방어코드; 제로스케일 문제 사전 방지
//	{
//		Vec_T_Scale.x = LL_G_ZeroScaleFloat;
//	}
//	else
//	{
//		Vec_T_Scale.x = 1 / _Vector3.x;
//
//	}
//
//	if (0.f == _Vector3.y)						// 방어코드; 제로스케일 문제 사전 방지
//	{
//		Vec_T_Scale.y = LL_G_ZeroScaleFloat;
//	}
//	else
//	{
//		Vec_T_Scale.y = 1 / _Vector3.y;
//
//	}
//
//	if (0.f == _Vector3.z)						// 방어코드; 제로스케일 문제 사전 방지
//	{
//		Vec_T_Scale.z = LL_G_ZeroScaleFloat;
//	}
//	else
//	{
//		Vec_T_Scale.z = 1 / _Vector3.z;
//
//	}
//
//	return Vec_T_Scale;
//}

//// RVO 버전
inline Vector3 GF_Set_InverseVector(const Vector3& Vec3_T_Source)
{
	return Vector3(
		(Vec3_T_Source.x != 0.f) ? (1.f / Vec3_T_Source.x) : LL_G_ZeroScaleFloat,
		(Vec3_T_Source.y != 0.f) ? (1.f / Vec3_T_Source.y) : LL_G_ZeroScaleFloat,
		(Vec3_T_Source.z != 0.f) ? (1.f / Vec3_T_Source.z) : LL_G_ZeroScaleFloat
	);
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