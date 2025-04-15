#include "pch.h"
#include "C_Transform.h"

C_Transform::C_Transform()
	: C_Component(_COMPONENT_TRANSFORM)
	, Vec3_M_RelativeScale(1.f, 1.f, 1.f)			// ������ �ʱ�ȭ; �������� (1.f, 1.f, 1.f) �� �������̹Ƿ� �ʱ�ȭ�� 1.f�� ��
	, Vec3_M_RelativeRotation(0.f, 0.f, 0.f)		// ȸ�� �ʱ�ȭ
	, Vec3_M_RelativePosition(0.f, 0.f, 0.f)		// ��ǥ �ʱ�ȭ

	, M_IsScaleDependent(false)						// �θ� ������Ʈ ���� �ʱ�ȭ
	
	, MAT_M_WorldMatrix{ 1.f, 0.f, 0.f, 0.f			// ����! ��ȯ������ �� ���� �����Ƿ� ������ ������ķ� �ʱ�ȭ!
						,0.f, 1.f, 0.f, 0.f
						,0.f, 0.f, 1.f, 0.f
						,0.f, 0.f, 0.f, 1.f }

{
	// ������(���ù���) �ʱ�ȭ; �����ڵ� : ������� ������ ���� �� �ٷ� ����(CPU ĳ�� ����)
	Vec3_M_RelativeDirection_s[_DIRECTION_RIGHT]   = { 1.f, 0.f, 0.f }
	, Vec3_M_RelativeDirection_s[_DIRECTION_UP]    = { 0.f, 1.f, 0.f }
	, Vec3_M_RelativeDirection_s[_DIRECTION_FRONT] = { 0.f, 0.f, 1.f };


	// ������� �ʱ�ȭ; �����ڵ� : ������� ������ ���� �� �ٷ� ����(CPU ĳ�� ����)
	Vec3_M_WorldMatrixDirection_s[_DIRECTION_RIGHT]   = { 1.f, 0.f, 0.f }
	, Vec3_M_WorldMatrixDirection_s[_DIRECTION_UP]    = { 0.f, 1.f, 0.f }
	, Vec3_M_WorldMatrixDirection_s[_DIRECTION_FRONT] = { 0.f, 0.f, 1.f };

}

C_Transform::C_Transform(const C_Transform& _Origin)
	: C_Component(_Origin)
	, Vec3_M_RelativeScale(_Origin.Vec3_M_RelativeScale)
	, Vec3_M_RelativeRotation(_Origin.Vec3_M_RelativeRotation)
	, Vec3_M_RelativePosition(_Origin.Vec3_M_RelativePosition)

	, Vec3_M_RelativeDirection_s{}
	, M_IsScaleDependent(false)

	, MAT_M_WorldMatrix{_Origin.MAT_M_WorldMatrix}
	, Vec3_M_WorldMatrixDirection_s{}
{
	// �����ڵ� : ������� ������ ���� �� �ٷ� ����(CPU ĳ�� ����)
	Vec3_M_RelativeDirection_s[_DIRECTION_RIGHT]   = _Origin.Vec3_M_RelativeDirection_s[_DIRECTION_RIGHT]
	, Vec3_M_RelativeDirection_s[_DIRECTION_UP]    = _Origin.Vec3_M_RelativeDirection_s[_DIRECTION_UP]
	, Vec3_M_RelativeDirection_s[_DIRECTION_FRONT] = _Origin.Vec3_M_RelativeDirection_s[_DIRECTION_FRONT];

	// �����ڵ� : ������� ������ ���� �� �ٷ� ����(CPU ĳ�� ����)
	Vec3_M_WorldMatrixDirection_s[_DIRECTION_RIGHT]   = _Origin.Vec3_M_WorldMatrixDirection_s[_DIRECTION_RIGHT]
	, Vec3_M_WorldMatrixDirection_s[_DIRECTION_UP]    = _Origin.Vec3_M_WorldMatrixDirection_s[_DIRECTION_UP]
	, Vec3_M_WorldMatrixDirection_s[_DIRECTION_FRONT] = _Origin.Vec3_M_WorldMatrixDirection_s[_DIRECTION_FRONT];

}

C_Transform::~C_Transform()
{
}

void C_Transform::MF_Prepare()													// ����, �Լ��� ���ϼ��� ���� �����ڿ��� ���� �Ἥ �ʱ�ȭ�ϴ� ������� ��ȯ�� �����ϴ� ���� ���� ��
{
}

void C_Transform::MF_ComponentTick()											// ����! ĳ���� �����Ƿ�, �Ϻη� ���ȭ�� ���� ���� ����! ����, ĳ���̳� ���ȭ �����ؼ� ����ȭ ����� �� ������ Ȯ���غ���
{
#ifdef _DEBUG				// ����� ����
	if ((0.f == Vec3_M_RelativeScale.x) || (0.f == Vec3_M_RelativeScale.y) || (0.f == Vec3_M_RelativeScale.z))						// ����ڵ�; ����! ������ ���� 0.f�� ���� ��쿡�� ������ ���� �� �����Ƿ� �˻�; ����, ������带 �� ���� �� �ִ� ����� �����غ���.
	{
		POPUP(L"", L"in C_Transform::MF_ComponentTick(), ")
		assert(true);
	}
#endif

	// ��ü���� ��� �帧
	// ��� ���� �ʱ�ȭ �� ȸ����� ���� �� ȸ�� ����� ������� ���� �� ���� ��� ���� �� �θ� ������(������ ���� ����) ���
	// 
	// ��ġ��� : ������ -> ȸ�� -> �̵�
	// ������ ��ķ� ��ȯ
	Matrix T_Mat_Scale = XMMatrixScaling(Vec3_M_RelativeScale.x, Vec3_M_RelativeScale.y, Vec3_M_RelativeScale.z);

	// ȸ�� ��ķ� ��ȯ; ����! ���ʹϾ� ������� �ڵ� �����Ͽ� ������� ���� �� ������ ȸ��������, �Ϻ� �������� �������� ������ ����!; ����, �̿� ���� ������ �� ���� ���� ������
	// ȸ�����͸� ���ʹϾ����� ��ȯ
	Vector3 Vec3_T_Rotation = XMQuaternionRotationRollPitchYaw(Vec3_M_RelativeRotation.x
                                                              , Vec3_M_RelativeRotation.y
                                                              , Vec3_M_RelativeRotation.z);
	Matrix MAT_T_Rotation = XMMatrixRotationQuaternion(Vec3_T_Rotation);																				// 

	// ��ǥ�̵��� ��ķ� ��ȯ
	Matrix MAT_T_Translation = XMMatrixTranslation(Vec3_M_RelativePosition.x
											, Vec3_M_RelativePosition.y
											, Vec3_M_RelativePosition.z);

	// ������� ��� ���
	MAT_M_WorldMatrix = T_Mat_Scale * MAT_T_Rotation * MAT_T_Translation;


	// ���⺤�� ���
	//// ���⺤�� �ʱ�ȭ; �������Ӹ��� ������ ������ ����; �����ڵ� : ������� ������ ���� �� �ٷ� ����(CPU ĳ�� ����)
	Vec3_M_RelativeDirection_s[_DIRECTION_RIGHT] = { 1.f, 0.f, 0.f }
	, Vec3_M_RelativeDirection_s[_DIRECTION_UP] = { 0.f, 1.f, 0.f }
	, Vec3_M_RelativeDirection_s[_DIRECTION_FRONT] = { 0.f, 0.f, 1.f };

	//// AoS ������ �����ߴٰ�, ������� ��� SoA�������� ���� �����Ƿ� �ٽñ� ���ƾ���; �����ڵ� : ������� ������ ���� �� �ٷ� ����(CPU ĳ�� ����)
	Vec3_M_WorldMatrixDirection_s[_DIRECTION_RIGHT]   = Vec3_M_RelativeDirection_s[_DIRECTION_RIGHT] = XMVector3TransformNormal(Vec3_M_RelativeDirection_s[_DIRECTION_RIGHT], MAT_T_Rotation)
	, Vec3_M_WorldMatrixDirection_s[_DIRECTION_UP]    = Vec3_M_RelativeDirection_s[_DIRECTION_UP]    = XMVector3TransformNormal(Vec3_M_RelativeDirection_s[_DIRECTION_UP], MAT_T_Rotation)
	, Vec3_M_WorldMatrixDirection_s[_DIRECTION_FRONT] = Vec3_M_RelativeDirection_s[_DIRECTION_FRONT] = XMVector3TransformNormal(Vec3_M_RelativeDirection_s[_DIRECTION_FRONT], MAT_T_Rotation);


	// �θ� ������Ʈ ���� ���
	// ����! �ݺ������� �θ��� �θ���� ������� �ʴ� ������ ������ �θ��� ��������� ��������̱� ����!
	C_Object* P_T_ParentObject = MF_Get_OwnerObject()->MF_Get_ParentObject();

	// ���ǹ��� ����� �ӽú��� ����
	//// ������带 ���̱� ����, ���ǹ� �ٱ����� ĳ����
	Matrix MAT_T_ParentScaleInverse = {};

	Vector3 Vec3_T_ParentDirection[_DIRECTION_END] = {};

	if (M_IsScaleDependent && (nullptr != P_T_ParentObject))			// ����ڵ�; ����! ������带 ���̱� ����, �귻ġ�� ���ҽ�Ű���� ���ǹ����� ��� ����
	{
		Vector3 vParentScale = P_T_ParentObject->MF_Get_TransformComponent()->MF_Get_RelativeScale();
		MAT_T_ParentScaleInverse = XMMatrixInverse(nullptr, XMMatrixScaling(vParentScale.x, vParentScale.y, vParentScale.z));
		MAT_M_WorldMatrix = MAT_M_WorldMatrix * MAT_T_ParentScaleInverse * P_T_ParentObject->MF_Get_TransformComponent()->MF_Get_WorldMatrix();

		C_Transform* T_ParentTransform = P_T_ParentObject->MF_Get_TransformComponent();

		Vec3_T_ParentDirection[_DIRECTION_RIGHT] = T_ParentTransform->MF_Get_RelativeDirection(_DIRECTION_RIGHT);
		Vec3_T_ParentDirection[_DIRECTION_UP]    = T_ParentTransform->MF_Get_RelativeDirection(_DIRECTION_UP);
		Vec3_T_ParentDirection[_DIRECTION_FRONT] = T_ParentTransform->MF_Get_RelativeDirection(_DIRECTION_FRONT);
	}
	else if(nullptr != P_T_ParentObject)
	{
		MAT_M_WorldMatrix *= MF_Get_OwnerObject()->MF_Get_ParentObject()->MF_Get_TransformComponent()->MF_Get_WorldMatrix();
	}

	// ���⺤�� ����ȭ
	// �ڵ� ����; ������� ���Ҹ� ���� ����������� ��
	//// ������(���ù���) ����ȭ
	Vec3_M_RelativeDirection_s[_DIRECTION_RIGHT].Normalize();
	Vec3_M_RelativeDirection_s[_DIRECTION_UP].Normalize();
	Vec3_M_RelativeDirection_s[_DIRECTION_FRONT].Normalize();

	//// ������� ����ȭ
	Vec3_M_WorldMatrixDirection_s[_DIRECTION_RIGHT].Normalize();
	Vec3_M_WorldMatrixDirection_s[_DIRECTION_UP].Normalize();
	Vec3_M_WorldMatrixDirection_s[_DIRECTION_FRONT].Normalize();
}

void C_Transform::MF_ComponentTickAfter()										// �����Լ�; ����! ��ġ����� Narrow Phase�� �� ���� ����
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
		C_Transform* T_ParentTransform = P_T_ParantObject->MF_Get_TransformComponent();
		
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