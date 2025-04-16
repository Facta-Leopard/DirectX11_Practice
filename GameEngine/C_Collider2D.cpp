#include "pch.h"
#include "C_Collider2D.h"

C_Collider2D::C_Collider2D()
	: C_Component(_COMPONENT_COLLIDER2D)
	, Vec3_M_ColliderScale{}

	, MAT_M_CollisionMatrix{}

	, M_IsDependent(false)

	, M_OverLapCount(0)
{

}

C_Collider2D::C_Collider2D(const C_Collider2D& _Origin)
	: C_Component(_Origin)
	, Vec3_M_ColliderScale{_Origin.Vec3_M_ColliderScale}

	, MAT_M_CollisionMatrix{_Origin.MAT_M_CollisionMatrix}

	, Vec3_M_CollisionDirection_s{}
	, M_IsDependent(false)

	, M_OverLapCount(0)
{
	// �����ڵ� : ������� ������ ���� �� �ٷ� ����(CPU ĳ�� ����)
	Vec3_M_CollisionDirection_s[_DIRECTION_RIGHT]   = _Origin.Vec3_M_CollisionDirection_s[_DIRECTION_RIGHT]
	, Vec3_M_CollisionDirection_s[_DIRECTION_UP]    = _Origin.Vec3_M_CollisionDirection_s[_DIRECTION_UP]
	, Vec3_M_CollisionDirection_s[_DIRECTION_FRONT] = _Origin.Vec3_M_CollisionDirection_s[_DIRECTION_FRONT];
}

C_Collider2D::~C_Collider2D()
{

}

void C_Collider2D::MF_Prepare()
{
}

void C_Collider2D::MF_ComponentTick()
{
	if (nullptr == MF_Get_OwnerObject())		// ����ڵ�; ������� ������ �����Ϸ� ����ȭ�� ������� �κ�; ����, �� �� �������� �����غ��� ���� ���ڴ�
	{
		POPUP_DEBUG(L"nullptr == MF_Get_OwnerObject", L"in C_Collider2D::MF_ComponentTick(), nullptr == MF_Get_OwnerObject")
	}
	else
	{
		MAT_M_CollisionMatrix = MF_Get_OwnerObject()->MF_Get_TransformComponent()->MF_Get_WorldMatrix();		// ����! ĳ�̸����̹Ƿ�, �̸� �� Ȱ���� �� �ֵ��� �Ͽ��� ��
	}

	// ������ ���
	//// ���������� ���ο� ���� ������� ������ ���� ������ ��� 
	if (true == M_IsDependent)
	{
		Vector3 Vec3_T_ObjectScale = MF_Get_OwnerObject()->MF_Get_TransformComponent()->MF_Get_RelativeScale();
		GF_Set_InverseVector(Vec3_T_ObjectScale);
		GF_Set_ScaleToMatrix(MAT_M_CollisionMatrix, Vec3_T_ObjectScale);
	}

	Vec3_M_ColliderScale = SF_Get_ScaleVector3FromMatrix(MAT_M_CollisionMatrix);

	// ���⺤�� ĳ��
	Vec3_M_CollisionDirection_s[_DIRECTION_RIGHT] = GF_Get_DirectionVector3FromMatrix(MAT_M_CollisionMatrix, _DIRECTION_RIGHT);
	Vec3_M_CollisionDirection_s[_DIRECTION_UP]    = GF_Get_DirectionVector3FromMatrix(MAT_M_CollisionMatrix, _DIRECTION_UP);
	Vec3_M_CollisionDirection_s[_DIRECTION_FRONT] = GF_Get_DirectionVector3FromMatrix(MAT_M_CollisionMatrix, _DIRECTION_FRONT);

	Vec3_M_CollisionDirection_s[_DIRECTION_RIGHT].Normalize();
	Vec3_M_CollisionDirection_s[_DIRECTION_UP].Normalize();
	Vec3_M_CollisionDirection_s[_DIRECTION_FRONT].Normalize();

	// ����
}

void C_Collider2D::MF_ComponentTickAfter()
{
	// ����, ����� ������ ������ �Ŵ������� �����ϴ� ���·� �����ϴ� ���� ���� ��
}

void C_Collider2D::MF_On_OverlapBegin(C_Collider2D* _Collider2D)
{
	++M_OverLapCount;
	MF_Nofify_OverlapBegin(_Collider2D);
}

void C_Collider2D::MF_On_OverlapIng(C_Collider2D* _Collider2D)
{
	MF_Nofify_OverlapIng(_Collider2D);
}

void C_Collider2D::MF_On_OverlapEnd(C_Collider2D* _Collider2D)
{
	--M_OverLapCount;
	MF_NofifyOverlapEnd(_Collider2D);
}

void C_Collider2D::MF_Nofify_OverlapBegin(C_Collider2D* _Collider2D)
{
	// ��ũ��Ʈ ������ ���� �ۼ��ʿ�
}

void C_Collider2D::MF_Nofify_OverlapIng(C_Collider2D* _Collider2D)
{
	// ��ũ��Ʈ ������ ���� �ۼ��ʿ�
}

void C_Collider2D::MF_NofifyOverlapEnd(C_Collider2D* _Collider2D)
{
	// ��ũ��Ʈ ������ ���� �ۼ��ʿ�
}