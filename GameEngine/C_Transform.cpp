#include "pch.h"
#include "C_Transform.h"
#include "C_ConstantBuffer.h"

C_Transform::C_Transform()
	: C_Component(_COMPONENT_TRANSFORM)
	, XM_VEC3_M_LocalScale(XMVectorSet(1.f, 1.f, 1.f, 0.f))			// ������ �ʱ�ȭ; �������� (1.f, 1.f, 1.f) �� �������̹Ƿ� �ʱ�ȭ�� 1.f�� ��
	, XM_VEC3_M_LocalRotation(XMVectorZero())						// ȸ�� �ʱ�ȭ
	, XM_VEC3_M_LocalPosition(XMVectorZero())						// ��ǥ �ʱ�ȭ

	, M_IsScaleDependent(false)						// �θ� ������Ʈ ���� �ʱ�ȭ
	
	, XM_MAT_M_WorldMatrix(XMMatrixIdentity())			// ����! ��ȯ������ �� ���� �����Ƿ� ������ ������ķ� �ʱ�ȭ!
{
	XM_VEC3_M_LocalDirection_s[_DIRECTION_RIGHT] = XMVectorSet(1.f, 0.f, 0.f, 0.f);
	XM_VEC3_M_LocalDirection_s[_DIRECTION_UP]    = XMVectorSet(0.f, 1.f, 0.f, 0.f);
	XM_VEC3_M_LocalDirection_s[_DIRECTION_FRONT] = XMVectorSet(0.f, 0.f, 1.f, 0.f);

	XM_VEC3_M_WorldMatrixDirection_s[_DIRECTION_RIGHT] = XM_VEC3_M_LocalDirection_s[_DIRECTION_RIGHT];
	XM_VEC3_M_WorldMatrixDirection_s[_DIRECTION_UP]    = XM_VEC3_M_LocalDirection_s[_DIRECTION_UP];
	XM_VEC3_M_WorldMatrixDirection_s[_DIRECTION_FRONT] = XM_VEC3_M_LocalDirection_s[_DIRECTION_FRONT];
}

C_Transform::C_Transform(const C_Transform& _Origin)
	: C_Component(_Origin)
	, XM_VEC3_M_LocalScale(_Origin.XM_VEC3_M_LocalScale)
	, XM_VEC3_M_LocalRotation(_Origin.XM_VEC3_M_LocalRotation)
	, XM_VEC3_M_LocalPosition(_Origin.XM_VEC3_M_LocalPosition)

	, M_IsScaleDependent(_Origin.M_IsScaleDependent)

	, XM_MAT_M_WorldMatrix(_Origin.XM_MAT_M_WorldMatrix)
{
	XM_VEC3_M_LocalDirection_s[_DIRECTION_RIGHT] = _Origin.XM_VEC3_M_LocalDirection_s[_DIRECTION_RIGHT];
	XM_VEC3_M_LocalDirection_s[_DIRECTION_UP]    = _Origin.XM_VEC3_M_LocalDirection_s[_DIRECTION_UP];
	XM_VEC3_M_LocalDirection_s[_DIRECTION_FRONT] = _Origin.XM_VEC3_M_LocalDirection_s[_DIRECTION_FRONT];

	XM_VEC3_M_WorldMatrixDirection_s[_DIRECTION_RIGHT] = _Origin.XM_VEC3_M_WorldMatrixDirection_s[_DIRECTION_RIGHT];
	XM_VEC3_M_WorldMatrixDirection_s[_DIRECTION_UP]    = _Origin.XM_VEC3_M_WorldMatrixDirection_s[_DIRECTION_UP];
	XM_VEC3_M_WorldMatrixDirection_s[_DIRECTION_FRONT] = _Origin.XM_VEC3_M_WorldMatrixDirection_s[_DIRECTION_FRONT];
}

C_Transform::~C_Transform()
{
}

void C_Transform::MF_Prepare()													// ����, �Լ��� ���ϼ��� ���� �����ڿ��� ���� �Ἥ �ʱ�ȭ�ϴ� ������� ��ȯ�� �����ϴ� ���� ���� ��
{
}

void C_Transform::MF_ComponentTick()											// ����! ĳ���� �����Ƿ�, �Ϻη� ���ȭ�� ���� ���� ����! ����, ĳ���̳� ���ȭ �����ؼ� ����ȭ ����� �� ������ Ȯ���غ���
{
	// ���ν����� ����ڵ�
	if (0.f == XMVectorGetX(XM_VEC3_M_LocalScale))
	{
		XM_VEC3_M_LocalScale = XMVectorSetX(XM_VEC3_M_LocalScale, G_LL_ZeroScaleFloat);
	}

	if (0.f == XMVectorGetY(XM_VEC3_M_LocalScale))
	{
		XM_VEC3_M_LocalScale = XMVectorSetY(XM_VEC3_M_LocalScale, G_LL_ZeroScaleFloat);
	}

	if (0.f == XMVectorGetZ(XM_VEC3_M_LocalScale))
	{
		XM_VEC3_M_LocalScale = XMVectorSetZ(XM_VEC3_M_LocalScale, G_LL_ZeroScaleFloat);
	}

	// ��ü���� ��� �帧
	// ��� ���� �ʱ�ȭ �� ȸ����� ���� �� ȸ�� ����� ������� ���� �� ���� ��� ���� �� �θ� ������(������ ���� ����) ���
	// 
	// ��ġ��� : ������ -> ȸ�� -> �̵�
	// ������ ��ķ� ��ȯ
	XMMATRIX XM_MAT_T_Scale = XMMatrixScalingFromVector(XM_VEC3_M_LocalScale);

	// ȸ�����͸� ���ʹϾ����� ��ȯ
	XMMATRIX XM_MAT_T_Rotation = XMMatrixRotationRollPitchYawFromVector(XM_VEC3_M_LocalRotation);

	// ��ǥ�̵��� ��ķ� ��ȯ
	XMMATRIX XM_MAT_T_Translation = XMMatrixTranslationFromVector(XM_VEC3_M_LocalPosition);

	// ������� ��� ���
	XM_MAT_M_WorldMatrix = XM_MAT_T_Scale * XM_MAT_T_Rotation * XM_MAT_T_Translation;

	// ���⺤�� ���
	//// ���⺤�� �ʱ�ȭ; �������Ӹ��� ������ ������ ����
	XM_VEC3_M_LocalDirection_s[_DIRECTION_RIGHT] = XMVectorSet(1.f, 0.f, 0.f, 0.f);
	XM_VEC3_M_LocalDirection_s[_DIRECTION_UP] = XMVectorSet(0.f, 1.f, 0.f, 0.f);
	XM_VEC3_M_LocalDirection_s[_DIRECTION_FRONT] = XMVectorSet(0.f, 0.f, 1.f, 0.f);

	//// AoS ������ �����ߴٰ�, ������� ��� SoA�������� ���� �����Ƿ� �ٽñ� ���ƾ���
	XM_VEC3_M_WorldMatrixDirection_s[_DIRECTION_RIGHT] = XMVector3TransformNormal(XM_VEC3_M_LocalDirection_s[_DIRECTION_RIGHT], XM_MAT_T_Rotation);
	XM_VEC3_M_WorldMatrixDirection_s[_DIRECTION_UP] = XMVector3TransformNormal(XM_VEC3_M_LocalDirection_s[_DIRECTION_UP], XM_MAT_T_Rotation);
	XM_VEC3_M_WorldMatrixDirection_s[_DIRECTION_FRONT] = XMVector3TransformNormal(XM_VEC3_M_LocalDirection_s[_DIRECTION_FRONT], XM_MAT_T_Rotation);

	// �θ� ������Ʈ ���� ���
	// ����! �ݺ������� �θ��� �θ���� ������� �ʴ� ������ ������ �θ��� ��������� ��������̱� ����!
	C_Object* P_T_ParentObject = MF_Get_OwnerObject()->MF_Get_ParentObject();

	if (nullptr != P_T_ParentObject)			// ����ڵ�; ����! ������带 ���̱� ����, �귻ġ�� ���ҽ�Ű���� ���ǹ����� ��� ����
	{
		C_Transform* T_ParentTransform = P_T_ParentObject->MF_Get_TransformComponent();
		XMMATRIX XM_MAT_T_ParentWorld = T_ParentTransform->MF_Get_WorldMatrix();

		// ������ ����޴��� ���
		if (true == M_IsScaleDependent)
		{
			XMVECTOR XM_VEC3_T_ParentScale = T_ParentTransform->MF_Get_LocalScale();
			XMMATRIX XM_MAT_T_ParentScaleInverse = XMMatrixInverse(nullptr, XMMatrixScalingFromVector(XM_VEC3_T_ParentScale));
			XM_MAT_M_WorldMatrix = XM_MAT_M_WorldMatrix * XM_MAT_T_ParentScaleInverse * XM_MAT_T_ParentWorld;
		}
		else
		{
			XM_MAT_M_WorldMatrix *= (P_T_ParentObject->MF_Get_TransformComponent()->MF_Get_WorldMatrix());
		}

		// ���⺤�� �ʱ�ȭ
		XM_VEC3_M_WorldMatrixDirection_s[_DIRECTION_RIGHT] = XMVectorSet(1.f, 0.f, 0.f, 0.f);
		XM_VEC3_M_WorldMatrixDirection_s[_DIRECTION_UP] = XMVectorSet(0.f, 1.f, 0.f, 0.f);
		XM_VEC3_M_WorldMatrixDirection_s[_DIRECTION_FRONT] = XMVectorSet(0.f, 0.f, 1.f, 0.f);

		XMVECTOR XM_Vec3_Scale, XM_Vec3_Rot, XM_Vec3_Trans;
		XMMatrixDecompose(&XM_Vec3_Scale, &XM_Vec3_Rot, &XM_Vec3_Trans, XM_MAT_M_WorldMatrix);
		XMMATRIX XM_MAT_T_ScaleInverse = XMMatrixInverse(nullptr, XMMatrixScalingFromVector(XM_Vec3_Scale));

		XM_VEC3_M_WorldMatrixDirection_s[_DIRECTION_RIGHT] = XMVector3TransformNormal(XM_VEC3_M_WorldMatrixDirection_s[_DIRECTION_RIGHT], XM_MAT_T_ScaleInverse * XM_MAT_M_WorldMatrix);
		XM_VEC3_M_WorldMatrixDirection_s[_DIRECTION_UP] = XMVector3TransformNormal(XM_VEC3_M_WorldMatrixDirection_s[_DIRECTION_UP], XM_MAT_T_ScaleInverse * XM_MAT_M_WorldMatrix);
		XM_VEC3_M_WorldMatrixDirection_s[_DIRECTION_FRONT] = XMVector3TransformNormal(XM_VEC3_M_WorldMatrixDirection_s[_DIRECTION_FRONT], XM_MAT_T_ScaleInverse * XM_MAT_M_WorldMatrix);

		//// ������� ����ȭ
		XM_VEC3_M_WorldMatrixDirection_s[_DIRECTION_RIGHT] = XMVector3Normalize(XM_VEC3_M_WorldMatrixDirection_s[_DIRECTION_RIGHT]);
		XM_VEC3_M_WorldMatrixDirection_s[_DIRECTION_UP] = XMVector3Normalize(XM_VEC3_M_WorldMatrixDirection_s[_DIRECTION_UP]);
		XM_VEC3_M_WorldMatrixDirection_s[_DIRECTION_FRONT] = XMVector3Normalize(XM_VEC3_M_WorldMatrixDirection_s[_DIRECTION_FRONT]);
	}
}

void C_Transform::MF_ComponentTickAfter()										// �����Լ�; ����! ��ġ����� Narrow Phase�� �� ���� ����
{
}

void C_Transform::MF_Bind_Transform()
{
	// Ʈ������ ������۸� ������
	C_ConstantBuffer* P_T_ConstantBuffer = C_Device::SF_Get_Instance()->MF_Get_ConstantBuffer(_CONSTANTBUFFER_TRANSFORM);

	// GPU ���޿� XM������ CPU ���� XM���� ��ȯ
	//// ����� ������ �״�� ����ϴ� ����
	//// �� ��� ��ȯ
	XMMATRIX XM_MAT_View = XMLoadFloat4x4(&G_DS_TransformVariable.SDK_XM_FLOAT4X4_ViewMatrix);

	//// �������� ��� ��ȯ
	XMMATRIX XM_MAT_Proj = XMLoadFloat4x4(&G_DS_TransformVariable.SDK_XM_FLOAT4X4_ProjectionMatrix);

	// ���
	//// ������������ ���� + �� ��� ���
	//// ��, ���� ����� �������� ����.
	XMMATRIX XM_MAT_WV = XM_MAT_M_WorldMatrix * XM_MAT_View;

	// ������������ (���� + ��) + �������� ��� ���
	XMMATRIX XM_MAT_WVP = XM_MAT_WV * XM_MAT_Proj;

	// CPU ����� XM������ GPU ���޿� XM���� ��ȯ
	//// ������� ���������� ����
	XMStoreFloat4x4(&G_DS_TransformVariable.SDK_XM_FLOAT4X4_WorldMatrix, XM_MAT_M_WorldMatrix);

	//// ������������ ���� + �� ��� ����
	XMStoreFloat4x4(&G_DS_TransformVariable.SDK_XM_FLOAT4X4_WorldViewMatrix, XM_MAT_WV);

	//// ������������ (���� + ��) + �������� ��� ����
	XMStoreFloat4x4(&G_DS_TransformVariable.SDK_XM_FLOAT4X4_WorldViewProjectionMatrix, XM_MAT_WVP);

	// ������ۿ� ������ ����
	P_T_ConstantBuffer->MF_Set_ConstantBufferByData(&G_DS_TransformVariable, sizeof(DS_Transform));
	P_T_ConstantBuffer->MF_Bind_ConstantBuffer();
}