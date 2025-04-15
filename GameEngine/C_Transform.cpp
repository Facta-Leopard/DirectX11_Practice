#include "pch.h"
#include "C_Transform.h"

C_Transform::C_Transform()
	: C_Component(_COMPONENT_TRANSFORM)
	, Vec3_M_RelativeScale(1.f, 1.f, 1.f)			// 스케일 초기화; 스케일은 (1.f, 1.f, 1.f) 가 원본값이므로 초기화를 1.f로 함
	, Vec3_M_RelativeRotation(0.f, 0.f, 0.f)		// 회전 초기화
	, Vec3_M_RelativePosition(0.f, 0.f, 0.f)		// 좌표 초기화

	, M_IsScaleDependent(false)						// 부모 오브젝트 연결 초기화
	
	, MAT_M_WorldMatrix{ 1.f, 0.f, 0.f, 0.f			// 유의! 변환용으로 쓸 수도 있으므로 무조건 단위행렬로 초기화!
						,0.f, 1.f, 0.f, 0.f
						,0.f, 0.f, 1.f, 0.f
						,0.f, 0.f, 0.f, 1.f }

{
	// 상대방향(로컬방향) 초기화; 개선코드 : 오버헤드 개선을 위해 한 줄로 수정(CPU 캐싱 감소)
	Vec3_M_RelativeDirection_s[_DIRECTION_RIGHT]   = { 1.f, 0.f, 0.f }
	, Vec3_M_RelativeDirection_s[_DIRECTION_UP]    = { 0.f, 1.f, 0.f }
	, Vec3_M_RelativeDirection_s[_DIRECTION_FRONT] = { 0.f, 0.f, 1.f };


	// 월드방향 초기화; 개선코드 : 오버헤드 개선을 위해 한 줄로 수정(CPU 캐싱 감소)
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
	// 개선코드 : 오버헤드 개선을 위해 한 줄로 수정(CPU 캐싱 감소)
	Vec3_M_RelativeDirection_s[_DIRECTION_RIGHT]   = _Origin.Vec3_M_RelativeDirection_s[_DIRECTION_RIGHT]
	, Vec3_M_RelativeDirection_s[_DIRECTION_UP]    = _Origin.Vec3_M_RelativeDirection_s[_DIRECTION_UP]
	, Vec3_M_RelativeDirection_s[_DIRECTION_FRONT] = _Origin.Vec3_M_RelativeDirection_s[_DIRECTION_FRONT];

	// 개선코드 : 오버헤드 개선을 위해 한 줄로 수정(CPU 캐싱 감소)
	Vec3_M_WorldMatrixDirection_s[_DIRECTION_RIGHT]   = _Origin.Vec3_M_WorldMatrixDirection_s[_DIRECTION_RIGHT]
	, Vec3_M_WorldMatrixDirection_s[_DIRECTION_UP]    = _Origin.Vec3_M_WorldMatrixDirection_s[_DIRECTION_UP]
	, Vec3_M_WorldMatrixDirection_s[_DIRECTION_FRONT] = _Origin.Vec3_M_WorldMatrixDirection_s[_DIRECTION_FRONT];

}

C_Transform::~C_Transform()
{
}

void C_Transform::MF_Prepare()													// 향후, 함수들 통일성을 위해 생성자에서 모듈로 써서 초기화하는 방법으로 전환도 생각하는 것이 좋을 듯
{
}

void C_Transform::MF_ComponentTick()											// 유의! 캐싱이 많으므로, 일부러 모듈화를 하지 않은 것임! 향후, 캐싱이나 모듈화 관련해서 최적화 방법이 더 없는지 확인해보자
{
#ifdef _DEBUG				// 디버그 전용
	if ((0.f == Vec3_M_RelativeScale.x) || (0.f == Vec3_M_RelativeScale.y) || (0.f == Vec3_M_RelativeScale.z))						// 방어코드; 유의! 스케일 값에 0.f가 들어가는 경우에는 문제가 생길 수 있으므로 검사; 향후, 오버헤드를 더 줄일 수 있는 방법을 생각해보자.
	{
		POPUP(L"", L"in C_Transform::MF_ComponentTick(), ")
		assert(true);
	}
#endif

	// 전체적인 계산 흐름
	// 상대 방향 초기화 → 회전행렬 생성 → 회전 결과로 월드방향 갱신 → 월드 행렬 생성 → 부모 의존성(스케일 포함 여부) 계산
	// 
	// 위치계산 : 스케일 -> 회전 -> 이동
	// 스케일 행렬로 변환
	Matrix T_Mat_Scale = XMMatrixScaling(Vec3_M_RelativeScale.x, Vec3_M_RelativeScale.y, Vec3_M_RelativeScale.z);

	// 회전 행렬로 변환; 유의! 쿼터니언 방식으로 코드 개선하여 오버헤드 감소 및 짐벌락 회피했으나, 일부 가독성이 떨어지는 문제가 있음!; 향후, 이에 대한 생각을 해 보는 것이 좋겠음
	// 회전벡터를 쿼터니언으로 변환
	Vector3 Vec3_T_Rotation = XMQuaternionRotationRollPitchYaw(Vec3_M_RelativeRotation.x
                                                              , Vec3_M_RelativeRotation.y
                                                              , Vec3_M_RelativeRotation.z);
	Matrix MAT_T_Rotation = XMMatrixRotationQuaternion(Vec3_T_Rotation);																				// 

	// 좌표이동을 행렬로 변환
	Matrix MAT_T_Translation = XMMatrixTranslation(Vec3_M_RelativePosition.x
											, Vec3_M_RelativePosition.y
											, Vec3_M_RelativePosition.z);

	// 월드공간 행렬 계산
	MAT_M_WorldMatrix = T_Mat_Scale * MAT_T_Rotation * MAT_T_Translation;


	// 방향벡터 계산
	//// 방향벡터 초기화; 매프레임마다 고정된 값으로 설정; 개선코드 : 오버헤드 개선을 위해 한 줄로 수정(CPU 캐싱 감소)
	Vec3_M_RelativeDirection_s[_DIRECTION_RIGHT] = { 1.f, 0.f, 0.f }
	, Vec3_M_RelativeDirection_s[_DIRECTION_UP] = { 0.f, 1.f, 0.f }
	, Vec3_M_RelativeDirection_s[_DIRECTION_FRONT] = { 0.f, 0.f, 1.f };

	//// AoS 구조로 설정했다가, 재검토한 결과 SoA구조보다 좋지 않으므로 다시금 갈아엎음; 개선코드 : 오버헤드 개선을 위해 한 줄로 수정(CPU 캐싱 감소)
	Vec3_M_WorldMatrixDirection_s[_DIRECTION_RIGHT]   = Vec3_M_RelativeDirection_s[_DIRECTION_RIGHT] = XMVector3TransformNormal(Vec3_M_RelativeDirection_s[_DIRECTION_RIGHT], MAT_T_Rotation)
	, Vec3_M_WorldMatrixDirection_s[_DIRECTION_UP]    = Vec3_M_RelativeDirection_s[_DIRECTION_UP]    = XMVector3TransformNormal(Vec3_M_RelativeDirection_s[_DIRECTION_UP], MAT_T_Rotation)
	, Vec3_M_WorldMatrixDirection_s[_DIRECTION_FRONT] = Vec3_M_RelativeDirection_s[_DIRECTION_FRONT] = XMVector3TransformNormal(Vec3_M_RelativeDirection_s[_DIRECTION_FRONT], MAT_T_Rotation);


	// 부모 오브젝트 누적 계산
	// 유의! 반복문으로 부모의 부모까지 계산하지 않는 이유는 어차피 부모의 멤버값들이 최종결과이기 때문!
	C_Object* P_T_ParentObject = MF_Get_OwnerObject()->MF_Get_ParentObject();

	// 조건문에 사용할 임시변수 선언
	//// 오버헤드를 줄이기 위해, 조건문 바깥에서 캐싱함
	Matrix MAT_T_ParentScaleInverse = {};

	Vector3 Vec3_T_ParentDirection[_DIRECTION_END] = {};

	if (M_IsScaleDependent && (nullptr != P_T_ParentObject))			// 방어코드; 유의! 오버헤드를 줄이기 위해, 브렌치를 감소시키고자 조건문으로 방식 변경
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

	// 방향벡터 정규화
	// 코드 개선; 오버헤드 감소를 위한 나열방식으로 함
	//// 상대방향(로컬방향) 정규화
	Vec3_M_RelativeDirection_s[_DIRECTION_RIGHT].Normalize();
	Vec3_M_RelativeDirection_s[_DIRECTION_UP].Normalize();
	Vec3_M_RelativeDirection_s[_DIRECTION_FRONT].Normalize();

	//// 월드방향 정규화
	Vec3_M_WorldMatrixDirection_s[_DIRECTION_RIGHT].Normalize();
	Vec3_M_WorldMatrixDirection_s[_DIRECTION_UP].Normalize();
	Vec3_M_WorldMatrixDirection_s[_DIRECTION_FRONT].Normalize();
}

void C_Transform::MF_ComponentTickAfter()										// 더미함수; 유의! 위치계산은 Narrow Phase로 쓸 일이 없음
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
	// 계산할 수 없는 부분이므로, 일부러 함수를 만들어서 실수 하지 않도록 만든 함수
	assert(true);
}

void C_Transform::MF_ConvertWorldMatrixToVectorDirection()
{
	// 계산할 수 없는 부분이므로, 일부러 함수를 만들어서 실수 하지 않도록 만든 함수
	assert(true);
}

#endif // _DEBUG