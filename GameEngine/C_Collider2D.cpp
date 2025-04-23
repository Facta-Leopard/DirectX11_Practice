#include "pch.h"
#include "C_Collider2D.h"

C_Collider2D::C_Collider2D()
	: C_Component(_COMPONENT_COLLIDER2D)
	, XM_VEC3_M_ColliderScale{}

	, XM_MAT_M_CollisionXMMATRIX{}

	, M_IsDependent(false)

	, M_OverLapCount(0)
{

}

C_Collider2D::C_Collider2D(const C_Collider2D& _Origin)
	: C_Component(_Origin)
	, XM_VEC3_M_ColliderScale{_Origin.XM_VEC3_M_ColliderScale }

	, XM_MAT_M_CollisionXMMATRIX{_Origin.XM_MAT_M_CollisionXMMATRIX }

	, XM_VEC3_M_CollisionDirection_s{}
	, M_IsDependent(false)

	, M_OverLapCount(0)
{
	// 개선코드 : 오버헤드 개선을 위해 한 줄로 수정(CPU 캐싱 감소)
	XM_VEC3_M_CollisionDirection_s[_DIRECTION_RIGHT]   = _Origin.XM_VEC3_M_CollisionDirection_s[_DIRECTION_RIGHT]
	, XM_VEC3_M_CollisionDirection_s[_DIRECTION_UP]    = _Origin.XM_VEC3_M_CollisionDirection_s[_DIRECTION_UP]
	, XM_VEC3_M_CollisionDirection_s[_DIRECTION_FRONT] = _Origin.XM_VEC3_M_CollisionDirection_s[_DIRECTION_FRONT];
}

C_Collider2D::~C_Collider2D()
{

}

void C_Collider2D::MF_Prepare()
{
}

void C_Collider2D::MF_ComponentTick()
{
	if (nullptr == MF_Get_OwnerObject())		// 방어코드; 디버깅이 없으면 컴파일러 최적화로 사라지는 부분; 향후, 좀 더 개선점을 생각해보는 것이 좋겠다
	{
		POPUP_DEBUG(L"nullptr == MF_Get_OwnerObject", L"in C_Collider2D::MF_ComponentTick(), nullptr == MF_Get_OwnerObject")
	}

	C_Transform* P_T_ParentTransform = MF_Get_OwnerObject()->MF_Get_TransformComponent();
	// 스케일 계산
	//// 독립적인지 여부에 따라 월드공간 배율에 따른 스케일 계산 
	if (true == M_IsDependent)
	{
		XMMATRIX XM_MAT_T_ParentWorld = P_T_ParentTransform->MF_Get_WorldMatrix();
		XMVECTOR XM_VEC3_T_ParentScale = P_T_ParentTransform->MF_Get_LocalScale();
		XMMATRIX XM_MAT_T_ParentScaleInverse = XMMatrixInverse(nullptr, XMMatrixScalingFromVector(XM_VEC3_T_ParentScale));
		XM_MAT_M_CollisionXMMATRIX = XM_MAT_M_CollisionXMMATRIX * XM_MAT_T_ParentScaleInverse * XM_MAT_T_ParentWorld;
	}
	else
	{
		XM_MAT_M_CollisionXMMATRIX = P_T_ParentTransform->MF_Get_WorldMatrix();		// 유의! 캐싱목적이므로, 이를 잘 활용할 수 있도록 하여야 함
	}

	// 방향벡터 초기화
	XM_VEC3_M_CollisionDirection_s[_DIRECTION_RIGHT] = XMVectorSet(1.f, 0.f, 0.f, 0.f);
	XM_VEC3_M_CollisionDirection_s[_DIRECTION_UP]    = XMVectorSet(0.f, 1.f, 0.f, 0.f);
	XM_VEC3_M_CollisionDirection_s[_DIRECTION_FRONT] = XMVectorSet(0.f, 0.f, 1.f, 0.f);

	XM_VEC3_M_ColliderScale = SF_Get_ScaleVector3FromMatrix(XM_MAT_M_CollisionXMMATRIX);

	// 방향벡터 캐싱
	XM_VEC3_M_CollisionDirection_s[_DIRECTION_RIGHT] = GF_Get_DirectionVector3FromMatrix(XM_MAT_M_CollisionXMMATRIX, _DIRECTION_RIGHT);
	XM_VEC3_M_CollisionDirection_s[_DIRECTION_UP]    = GF_Get_DirectionVector3FromMatrix(XM_MAT_M_CollisionXMMATRIX, _DIRECTION_UP);
	XM_VEC3_M_CollisionDirection_s[_DIRECTION_FRONT] = GF_Get_DirectionVector3FromMatrix(XM_MAT_M_CollisionXMMATRIX, _DIRECTION_FRONT);

	// 방향벡터 정규화
	XM_VEC3_M_CollisionDirection_s[_DIRECTION_RIGHT] = XMVector3Normalize(XM_VEC3_M_CollisionDirection_s[_DIRECTION_RIGHT]);
	XM_VEC3_M_CollisionDirection_s[_DIRECTION_UP]    = XMVector3Normalize(XM_VEC3_M_CollisionDirection_s[_DIRECTION_UP]);
	XM_VEC3_M_CollisionDirection_s[_DIRECTION_FRONT] = XMVector3Normalize(XM_VEC3_M_CollisionDirection_s[_DIRECTION_FRONT]);

	// 최종
}

void C_Collider2D::MF_ComponentTickAfter()
{
	// 향후, 디버그 렌더는 별도로 매니저에서 관리하는 형태로 개선하는 것이 좋을 듯
}

void C_Collider2D::MF_Set_ColliderScale(XMVECTOR _XM_VEC3_ColliderScale)
{
	XM_VEC3_M_ColliderScale = _XM_VEC3_ColliderScale;

	E_COLLIDER_TYPE T_ColliderType = C_StageManager::SF_Get_Instance()->MF_Get_CurrentStage()->MF_Get_ColliderType();

	switch (T_ColliderType)
	{

	case _COLLIDER_2D_TOPVEIW:
	case _COLLIDER_2D_ISOMETRICVIEW:

		XM_VEC3_M_ColliderScale = XMVectorSetY(_XM_VEC3_ColliderScale, 0.f);

		break;
	default:

		XM_VEC3_M_ColliderScale = XMVectorSetZ(_XM_VEC3_ColliderScale, 0.f);

		break;
	}
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
	// 스크립트 구성시 마저 작성필요
}

void C_Collider2D::MF_Nofify_OverlapIng(C_Collider2D* _Collider2D)
{
	// 스크립트 구성시 마저 작성필요
}

void C_Collider2D::MF_NofifyOverlapEnd(C_Collider2D* _Collider2D)
{
	// 스크립트 구성시 마저 작성필요
}