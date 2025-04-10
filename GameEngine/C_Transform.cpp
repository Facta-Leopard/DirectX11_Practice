#include "pch.h"
#include "C_Transform.h"

C_Transform::C_Transform()
	: C_Component(_COMPONENT_TRANSFORM)
	, Vec3_M_RelativePosition(0.f, 0.f, 0.f)		// 좌표 초기화
	, Vec3_M_RelativeScale(1.f, 1.f, 1.f)			// 스케일 초기화; 스케일은 (1.f, 1.f, 1.f) 가 원본값이므로 초기화를 1.f로 함
	, Vec3_M_RelativeRotation(0.f, 0.f, 0.f)		// 회전 초기화
	, Vec3_M_RelativeDirection(0.f, 0.f, 0.f)		// 방향 초기화
	, M_IsScaleDependent(false)							// 부모 오브젝트 연결 초기화
	
	, MAT_M_WorldMatrix{ 1.f, 0.f, 0.f, 0.f,		// 유의! 변환용으로 쓸 수도 있으므로 무조건 단위행렬로 초기화 해야함!
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
	// 향후, 구조화 버퍼관련 클래스 생성 후 함수 작성 필요
}

Vector3 C_Transform::MF_ConvertWorldMatrixToVectorPosition()
{
	return Vector3();
}

Vector3 C_Transform::MF_ConvertWorldMatrixToVectorScale()
{
	C_Object* P_T_ParantObject = MF_Get_OwnerObject()->MF_Get_ParentObject();
	
	bool T_Scale = M_IsScaleDependent;

	while ((nullptr != P_T_ParantObject) && T_Scale)				// 방어코드
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
