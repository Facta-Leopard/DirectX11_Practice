#include "pch.h"
#include "C_Transform.h"

C_Transform::C_Transform()
	: C_Component(_COMPONENT_TRANSFORM)
	, Vec3_M_RelativePosition(0.f, 0.f, 0.f)		// 좌표 초기화
	, Vec3_M_RelativeScale(1.f, 1.f, 1.f)			// 스케일 초기화; 스케일은 (1.f, 1.f, 1.f) 가 원본값이므로 초기화를 1.f로 함
	, Vec3_M_RelativeRotation(0.f, 0.f, 0.f)		// 회전 초기화
	, Vec3_M_RelativeDirection(0.f, 0.f, 0.f)		// 방향 초기화
	, M_IsScaleDependent(false)							// 부모 오브젝트 연결 초기화
	
	, MAT_M_WorldMatrix{ 1.f, 0.f, 0.f, 0.f		// 유의! 변환용으로 쓸 수도 있으므로 무조건 단위행렬로 초기화 해야함!
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

void C_Transform::MF_Prepare()						// 초기화 함수; 향후, 함수들 통일성을 위해 생성자에서 모듈로 써서 초기화하는 방법으로 전환도 생각하는 것이 좋을 듯
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
	// 향후, 구조화 버퍼관련 클래스 생성 후 함수 작성 필요
}

Vector3 C_Transform::MF_ConvertWorldMatrixToVectorPosition()
{
	return Vector3();
}

Vector3 C_Transform::MF_ConvertWorldMatrixToVectorScale()						// 유의! 오버헤드를 줄이기 위해 직접접근을 선택함
{
	C_Object* P_T_ParantObject = MF_Get_OwnerObject()->MF_Get_ParentObject();
	
	Vector3 T_WorldSpaceScale = Vec3_M_RelativeScale;

	bool T_IsDependent = M_IsScaleDependent;

	while (T_IsDependent && (nullptr != P_T_ParantObject))						// 방어코드; 향후, 더 효율적인 오버헤드 감소방법이 있을 지 생각해보자
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
	// 계산할 수 없는 부분이므로, 일부러 함수를 만들어서 실수 하지 않도록 만든 함수
	assert(true);
}

void C_Transform::MF_ConvertWorldMatrixToVectorDirection()
{
	// 계산할 수 없는 부분이므로, 일부러 함수를 만들어서 실수 하지 않도록 만든 함수
	assert(true);
}

#endif // _DEBUG