#include "pch.h"
#include "C_Transform.h"
#include "C_ConstantBuffer.h"

C_Transform::C_Transform()
	: C_Component(_COMPONENT_TRANSFORM)
	, XM_VEC3_M_LocalScale(XMVectorSet(1.f, 1.f, 1.f, 0.f))			// 스케일 초기화; 스케일은 (1.f, 1.f, 1.f) 가 원본값이므로 초기화를 1.f로 함
	, XM_VEC3_M_LocalRotation(XMVectorZero())						// 회전 초기화
	, XM_VEC3_M_LocalPosition(XMVectorZero())						// 좌표 초기화

	, M_IsScaleDependent(false)						// 부모 오브젝트 연결 초기화
	
	, XM_MAT_M_WorldMatrix(XMMatrixIdentity())			// 유의! 변환용으로 쓸 수도 있으므로 무조건 단위행렬로 초기화!
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

void C_Transform::MF_Prepare()													// 향후, 함수들 통일성을 위해 생성자에서 모듈로 써서 초기화하는 방법으로 전환도 생각하는 것이 좋을 듯
{
}

void C_Transform::MF_ComponentTick()											// 유의! 캐싱이 많으므로, 일부러 모듈화를 하지 않은 것임! 향후, 캐싱이나 모듈화 관련해서 최적화 방법이 더 없는지 확인해보자
{
	// 제로스케일 방어코드
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

	// 전체적인 계산 흐름
	// 상대 방향 초기화 → 회전행렬 생성 → 회전 결과로 월드방향 갱신 → 월드 행렬 생성 → 부모 의존성(스케일 포함 여부) 계산
	// 
	// 위치계산 : 스케일 -> 회전 -> 이동
	// 스케일 행렬로 변환
	XMMATRIX XM_MAT_T_Scale = XMMatrixScalingFromVector(XM_VEC3_M_LocalScale);

	// 회전벡터를 쿼터니언으로 변환
	XMMATRIX XM_MAT_T_Rotation = XMMatrixRotationRollPitchYawFromVector(XM_VEC3_M_LocalRotation);

	// 좌표이동을 행렬로 변환
	XMMATRIX XM_MAT_T_Translation = XMMatrixTranslationFromVector(XM_VEC3_M_LocalPosition);

	// 월드공간 행렬 계산
	XM_MAT_M_WorldMatrix = XM_MAT_T_Scale * XM_MAT_T_Rotation * XM_MAT_T_Translation;

	// 방향벡터 계산
	//// 방향벡터 초기화; 매프레임마다 고정된 값으로 설정
	XM_VEC3_M_LocalDirection_s[_DIRECTION_RIGHT] = XMVectorSet(1.f, 0.f, 0.f, 0.f);
	XM_VEC3_M_LocalDirection_s[_DIRECTION_UP] = XMVectorSet(0.f, 1.f, 0.f, 0.f);
	XM_VEC3_M_LocalDirection_s[_DIRECTION_FRONT] = XMVectorSet(0.f, 0.f, 1.f, 0.f);

	//// AoS 구조로 설정했다가, 재검토한 결과 SoA구조보다 좋지 않으므로 다시금 갈아엎음
	XM_VEC3_M_WorldMatrixDirection_s[_DIRECTION_RIGHT] = XMVector3TransformNormal(XM_VEC3_M_LocalDirection_s[_DIRECTION_RIGHT], XM_MAT_T_Rotation);
	XM_VEC3_M_WorldMatrixDirection_s[_DIRECTION_UP] = XMVector3TransformNormal(XM_VEC3_M_LocalDirection_s[_DIRECTION_UP], XM_MAT_T_Rotation);
	XM_VEC3_M_WorldMatrixDirection_s[_DIRECTION_FRONT] = XMVector3TransformNormal(XM_VEC3_M_LocalDirection_s[_DIRECTION_FRONT], XM_MAT_T_Rotation);

	// 부모 오브젝트 누적 계산
	// 유의! 반복문으로 부모의 부모까지 계산하지 않는 이유는 어차피 부모의 멤버값들이 최종결과이기 때문!
	C_Object* P_T_ParentObject = MF_Get_OwnerObject()->MF_Get_ParentObject();

	if (nullptr != P_T_ParentObject)			// 방어코드; 유의! 오버헤드를 줄이기 위해, 브렌치를 감소시키고자 조건문으로 방식 변경
	{
		C_Transform* T_ParentTransform = P_T_ParentObject->MF_Get_TransformComponent();
		XMMATRIX XM_MAT_T_ParentWorld = T_ParentTransform->MF_Get_WorldMatrix();

		// 스케일 영향받는지 계산
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

		// 방향벡터 초기화
		XM_VEC3_M_WorldMatrixDirection_s[_DIRECTION_RIGHT] = XMVectorSet(1.f, 0.f, 0.f, 0.f);
		XM_VEC3_M_WorldMatrixDirection_s[_DIRECTION_UP] = XMVectorSet(0.f, 1.f, 0.f, 0.f);
		XM_VEC3_M_WorldMatrixDirection_s[_DIRECTION_FRONT] = XMVectorSet(0.f, 0.f, 1.f, 0.f);

		XMVECTOR XM_Vec3_Scale, XM_Vec3_Rot, XM_Vec3_Trans;
		XMMatrixDecompose(&XM_Vec3_Scale, &XM_Vec3_Rot, &XM_Vec3_Trans, XM_MAT_M_WorldMatrix);
		XMMATRIX XM_MAT_T_ScaleInverse = XMMatrixInverse(nullptr, XMMatrixScalingFromVector(XM_Vec3_Scale));

		XM_VEC3_M_WorldMatrixDirection_s[_DIRECTION_RIGHT] = XMVector3TransformNormal(XM_VEC3_M_WorldMatrixDirection_s[_DIRECTION_RIGHT], XM_MAT_T_ScaleInverse * XM_MAT_M_WorldMatrix);
		XM_VEC3_M_WorldMatrixDirection_s[_DIRECTION_UP] = XMVector3TransformNormal(XM_VEC3_M_WorldMatrixDirection_s[_DIRECTION_UP], XM_MAT_T_ScaleInverse * XM_MAT_M_WorldMatrix);
		XM_VEC3_M_WorldMatrixDirection_s[_DIRECTION_FRONT] = XMVector3TransformNormal(XM_VEC3_M_WorldMatrixDirection_s[_DIRECTION_FRONT], XM_MAT_T_ScaleInverse * XM_MAT_M_WorldMatrix);

		//// 월드방향 정규화
		XM_VEC3_M_WorldMatrixDirection_s[_DIRECTION_RIGHT] = XMVector3Normalize(XM_VEC3_M_WorldMatrixDirection_s[_DIRECTION_RIGHT]);
		XM_VEC3_M_WorldMatrixDirection_s[_DIRECTION_UP] = XMVector3Normalize(XM_VEC3_M_WorldMatrixDirection_s[_DIRECTION_UP]);
		XM_VEC3_M_WorldMatrixDirection_s[_DIRECTION_FRONT] = XMVector3Normalize(XM_VEC3_M_WorldMatrixDirection_s[_DIRECTION_FRONT]);
	}
}

void C_Transform::MF_ComponentTickAfter()										// 더미함수; 유의! 위치계산은 Narrow Phase로 쓸 일이 없음
{
}

void C_Transform::MF_Bind_Transform()
{
	// 트랜스폼 전용버퍼를 가져옴
	C_ConstantBuffer* P_T_ConstantBuffer = C_Device::SF_Get_Instance()->MF_Get_ConstantBuffer(_CONSTANTBUFFER_TRANSFORM);

	// GPU 전달용 XM구조를 CPU 계산용 XM으로 전환
	//// 월드는 기존값 그대로 사용하니 생략
	//// 뷰 행렬 변환
	XMMATRIX XM_MAT_View = XMLoadFloat4x4(&G_DS_TransformVariable.SDK_XM_FLOAT4X4_ViewMatrix);

	//// 프로젝션 행렬 변환
	XMMATRIX XM_MAT_Proj = XMLoadFloat4x4(&G_DS_TransformVariable.SDK_XM_FLOAT4X4_ProjectionMatrix);

	// 계산
	//// 전역변수에서 월드 + 뷰 행렬 계산
	//// 단, 월드 행렬은 기존값을 쓴다.
	XMMATRIX XM_MAT_WV = XM_MAT_M_WorldMatrix * XM_MAT_View;

	// 전역변수에서 (월드 + 뷰) + 프로젝션 행렬 계산
	XMMATRIX XM_MAT_WVP = XM_MAT_WV * XM_MAT_Proj;

	// CPU 연산용 XM구조를 GPU 전달용 XM으로 전환
	//// 월드행렬 전역변수에 삽입
	XMStoreFloat4x4(&G_DS_TransformVariable.SDK_XM_FLOAT4X4_WorldMatrix, XM_MAT_M_WorldMatrix);

	//// 전역변수에서 월드 + 뷰 행렬 삽입
	XMStoreFloat4x4(&G_DS_TransformVariable.SDK_XM_FLOAT4X4_WorldViewMatrix, XM_MAT_WV);

	//// 전역변수에서 (월드 + 뷰) + 프로젝션 행렬 삽입
	XMStoreFloat4x4(&G_DS_TransformVariable.SDK_XM_FLOAT4X4_WorldViewProjectionMatrix, XM_MAT_WVP);

	// 상수버퍼에 데이터 삽입
	P_T_ConstantBuffer->MF_Set_ConstantBufferByData(&G_DS_TransformVariable, sizeof(DS_Transform));
	P_T_ConstantBuffer->MF_Bind_ConstantBuffer();
}