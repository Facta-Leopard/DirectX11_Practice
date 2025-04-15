#include "pch.h"
#include "C_Collider2D.h"

C_Collider2D::C_Collider2D()
	: C_Component(_COMPONENT_COLLIDER2D)
	, Vec3_M_ColliderScale{}

	, MAT_M_WorldCollision{}

	, M_IsDependent(false)

	, M_OverLapCount(0)
{

}

C_Collider2D::C_Collider2D(const C_Collider2D& _Origin)
	: C_Component(_Origin)
	, Vec3_M_ColliderScale{_Origin.Vec3_M_ColliderScale }

	, MAT_M_WorldCollision{_Origin .MAT_M_WorldCollision }

	, Vec3_M_WorldMatrixDirection_s{}
	, M_IsDependent(false)

	, M_OverLapCount(0)
{
	// 개선코드 : 오버헤드 개선을 위해 한 줄로 수정(CPU 캐싱 감소)
	Vec3_M_WorldMatrixDirection_s[_DIRECTION_RIGHT] = _Origin.Vec3_M_WorldMatrixDirection_s[_DIRECTION_RIGHT]
	, Vec3_M_WorldMatrixDirection_s[_DIRECTION_UP] = _Origin.Vec3_M_WorldMatrixDirection_s[_DIRECTION_UP]
	, Vec3_M_WorldMatrixDirection_s[_DIRECTION_FRONT] = _Origin.Vec3_M_WorldMatrixDirection_s[_DIRECTION_FRONT];
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
	else
	{
		MAT_M_WorldCollision = MF_Get_OwnerObject()->MF_Get_TransformComponent()->MF_Get_WorldMatrix();		// 유의! 캐싱목적이므로, 이를 잘 활용할 수 있도록 하여야 함
	}

	// 스케일 계산
	//// 독립적인지 여부에 따라 월드공간 배율에 따른 스케일 계산 
	if (true == M_IsDependent)
	{
		Vector3 Vec3_T_ObjectScale = MF_Get_OwnerObject()->MF_Get_TransformComponent()->MF_Get_RelativeScale();
		GF_Apply_InverseVector(Vec3_T_ObjectScale);
		GF_Apply_ScaleToMatrix(MAT_M_WorldCollision, Vec3_T_ObjectScale);
	}

	SF_Extract_ScaleFromMatrix(MAT_M_WorldCollision)

	// 방향벡터 캐싱


	// 최종
}

void C_Collider2D::MF_ComponentTickAfter()
{
	// 향후, 디버그 렌더는 별도로 매니저에서 관리하는 형태로 개선하는 것이 좋을 듯
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
