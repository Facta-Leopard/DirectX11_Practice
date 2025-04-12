#include "pch.h"
#include "C_Transform.h"

C_Transform::C_Transform()
	: C_Component(_COMPONENT_TRANSFORM)
	, Vec3_M_RelativePosition(0.f, 0.f, 0.f)		// ��ǥ �ʱ�ȭ
	, Vec3_M_RelativeScale(1.f, 1.f, 1.f)			// ������ �ʱ�ȭ; �������� (1.f, 1.f, 1.f) �� �������̹Ƿ� �ʱ�ȭ�� 1.f�� ��
	, Vec3_M_RelativeRotation(0.f, 0.f, 0.f)		// ȸ�� �ʱ�ȭ
	, Vec3_M_RelativeDirection(0.f, 0.f, 0.f)		// ���� �ʱ�ȭ
	, M_IsScaleDependent(false)							// �θ� ������Ʈ ���� �ʱ�ȭ
	
	, MAT_M_WorldMatrix{ 1.f, 0.f, 0.f, 0.f		// ����! ��ȯ������ �� ���� �����Ƿ� ������ ������ķ� �ʱ�ȭ �ؾ���!
						,0.f, 1.f, 0.f, 0.f
						,0.f, 0.f, 1.f, 0.f
						,0.f, 0.f, 0.f, 1.f }
	, Vec3_WorldMatrixDirection(0.f, 0.f, 0.f)
{
}

C_Transform::C_Transform(const C_Transform& _Origin)
	: C_Component(_Origin)
	, Vec3_M_RelativePosition(_Origin.Vec3_M_RelativeDirection)
	, Vec3_M_RelativeScale(_Origin.Vec3_M_RelativeScale)
	, Vec3_M_RelativeRotation(_Origin.Vec3_M_RelativeRotation)
	, Vec3_M_RelativeDirection(_Origin.Vec3_M_RelativeDirection)
	, M_IsScaleDependent(false)

	, MAT_M_WorldMatrix{_Origin.MAT_M_WorldMatrix}
	, Vec3_WorldMatrixDirection(_Origin.Vec3_WorldMatrixDirection)
{
}

C_Transform::~C_Transform()
{
}

void C_Transform::MF_Prepare()						// �ʱ�ȭ �Լ�; ����, �Լ��� ���ϼ��� ���� �����ڿ��� ���� �Ἥ �ʱ�ȭ�ϴ� ������� ��ȯ�� �����ϴ� ���� ���� ��
{
}

void C_Transform::MF_ComponentTick()
{
	{
		POPUP_DEBUG(L"", L"")
	}
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

Vector3 C_Transform::MF_ConvertWorldMatrixToVectorScale()						// ����! ������带 ���̱� ���� ���������� ������
{
	C_Object* P_T_ParantObject = MF_Get_OwnerObject()->MF_Get_ParentObject();
	
	Vector3 T_WorldSpaceScale = Vec3_M_RelativeScale;

	bool T_IsDependent = M_IsScaleDependent;

	while (T_IsDependent && (nullptr != P_T_ParantObject))						// ����ڵ�; ����, �� ȿ������ ������� ���ҹ���� ���� �� �����غ���
	{
		C_Transform* T_ParentTransform = P_T_ParantObject->MF_Get_ComponentByReturnType<C_Transform>();
		
		T_WorldSpaceScale *= T_ParentTransform->MF_Get_RelativeScale();

		T_IsDependent = T_ParentTransform->MF_Get_IsScaleDependent();

		P_T_ParantObject = P_T_ParantObject->MF_Get_ParentObject();
	}
	return T_WorldSpaceScale;
}

#ifdef _DEBUG

void C_Transform::MF_ConvertWorldMatrixToVectorRotation()
{
	// ����� �� ���� �κ��̹Ƿ�, �Ϻη� �Լ��� ���� �Ǽ� ���� �ʵ��� ���� �Լ�
	assert(true);
}

void C_Transform::MF_ConvertWorldMatrixToVectorDirection()
{
	// ����� �� ���� �κ��̹Ƿ�, �Ϻη� �Լ��� ���� �Ǽ� ���� �ʵ��� ���� �Լ�
	assert(true);
}

#endif // _DEBUG