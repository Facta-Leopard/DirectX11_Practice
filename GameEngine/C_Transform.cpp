#include "pch.h"
#include "C_Transform.h"

C_Transform::C_Transform()
	: C_Component(_COMPONENT_TRANSFORM)
	, Vec3_M_RelativePosition(0.f, 0.f, 0.f)		// ��ǥ �ʱ�ȭ
	, Vec3_M_RelativeScale(1.f, 1.f, 1.f)			// ������ �ʱ�ȭ; �������� (1.f, 1.f, 1.f) �� �������̹Ƿ� �ʱ�ȭ�� 1.f�� ��
	, Vec3_M_RelativeRotation(0.f, 0.f, 0.f)		// ȸ�� �ʱ�ȭ
	, Vec3_M_RelativeDirection(0.f, 0.f, 0.f)		// ���� �ʱ�ȭ
	, M_IsScaleDependent(false)							// �θ� ������Ʈ ���� �ʱ�ȭ
	
	, MAT_M_WorldMatrix{ 1.f, 0.f, 0.f, 0.f,		// ����! ��ȯ������ �� ���� �����Ƿ� ������ ������ķ� �ʱ�ȭ �ؾ���!
						0.f, 1.f, 0.f, 0.f,
						0.f, 0.f, 1.f, 0.f,
						0.f, 0.f, 0.f, 1.f }
	, Vec3_WorldMatrixDirection(0.f, 0.f, 0.f)
{
}

C_Transform::C_Transform(const C_Transform& _Origin)
	: C_Component(_Origin)
{
}

C_Transform::~C_Transform()
{
}

void C_Transform::MF_Prepare()
{
}

void C_Transform::MF_ComponentTick()
{
}

void C_Transform::MF_ComponentTickAfter()
{
}

void C_Transform::MF_Bind_Register()
{
	// ����, ����ȭ ���۰��� Ŭ���� ���� �� �Լ� �ۼ� �ʿ�
}

Vector3 C_Transform::MF_ConvertWorldMatrixToVectorPosition()
{
	return Vector3();
}

Vector3 C_Transform::MF_ConvertWorldMatrixToVectorScale()
{
	C_Object* P_T_ParantObject = MF_Get_OwnerObject()->MF_Get_ParentObject();
	
	bool T_Scale = M_IsScaleDependent;

	while ((nullptr != P_T_ParantObject) && T_Scale)				// ����ڵ�
	{
		C_Transform* T_Transform = P_T_ParantObject->MF_Get_ComponentByReturnType<C_Transform>();

	}

	return Vector3();
}

Vector3 C_Transform::MF_ConvertWorldMatrixToVectorRotation()
{
	return Vector3();
}

Vector3 C_Transform::MF_ConvertWorldMatrixToVectorDirection()
{
	return Vector3();
}
