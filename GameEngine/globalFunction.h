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

// ��Ʈ���� ���� �����Լ�
// �������� �ϸ� ������尡 �پ��� ȿ���� �ִ�.
//// ��Ʈ�������� ���ͷ� �̾Ƴ��� �뵵�� ���� �Լ�
//// ������ ������ �ͼ����� �ʴ�..
//// NRVO ����; inline �ɷ��־ �����Ϸ� ����ȭ�� �ȵ� �� �����Ƿ� �ּ�ó���� �� 
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

//// RVO ����
inline Vector3 SF_Extract_ScaleFromMatrix(const Matrix& _Matrix)
{
	return Vector3(
		sqrtf((_Matrix._11 * _Matrix._11) + (_Matrix._21 * _Matrix._21) + (_Matrix._31 * _Matrix._31)),
		sqrtf((_Matrix._12 * _Matrix._12) + (_Matrix._22 * _Matrix._22) + (_Matrix._32 * _Matrix._32)),
		sqrtf((_Matrix._13 * _Matrix._13) + (_Matrix._23 * _Matrix._13) + (_Matrix._33 * _Matrix._33))
	);
}

// ����ȭ �ּ�
//// ���ϰ��� Right, Up, Look ���� ���̸� ���� ������ �����ϰ� (Vec3_T_Scale)
//// ���� ���� ���� ���� ���� �� RVO + inline ����ȭ ����
//// MAT_M_Source�� �������� ���Ե� ��ȯ ����̾�� ��


//// ��Ʈ���� �����ϸ� ����
//// ������ ������ �ͼ����� �ʴ�.
inline void GF_Apply_ScaleToMatrix(Matrix& _Matrix, const Vector3& V_Scale)
{
	// X�� ���� ���� (Right)
	_Matrix._11 *= V_Scale.x;
	_Matrix._12 *= V_Scale.x;
	_Matrix._13 *= V_Scale.x;

	// Y�� ���� ���� (Up)
	_Matrix._21 *= V_Scale.y;
	_Matrix._22 *= V_Scale.y;
	_Matrix._23 *= V_Scale.y;

	// Z�� ���� ���� (Look)
	_Matrix._31 *= V_Scale.z;
	_Matrix._32 *= V_Scale.z;
	_Matrix._33 *= V_Scale.z;

	// ����! _41, _42, _43�� ��ġ ���� ������ �־ �ǵ帮�� ������� ���ϱ� ���� ����
}


// Vector3 ���� �����Լ�
//// Vector3 ���� �������Ѵ�.
inline Vector3 GF_Apply_InverseVector(const Vector3& _Vector3)
{
	Vector3 Vec_T_Scale = {};

	if (0.f == _Vector3.x)						// ����ڵ�; ���ν����� ���� ���� ����
	{
		Vec_T_Scale.x = LL_G_ZeroScaleFloat;
	}
	else
	{
		Vec_T_Scale.x = 1 / _Vector3.x;

	}

	if (0.f == _Vector3.y)						// ����ڵ�; ���ν����� ���� ���� ����
	{
		Vec_T_Scale.y = LL_G_ZeroScaleFloat;
	}
	else
	{
		Vec_T_Scale.y = 1 / _Vector3.y;

	}

	if (0.f == _Vector3.z)						// ����ڵ�; ���ν����� ���� ���� ����
	{
		Vec_T_Scale.z = LL_G_ZeroScaleFloat;
	}
	else
	{
		Vec_T_Scale.z = 1 / _Vector3.z;

	}

	return Vec_T_Scale;
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




















