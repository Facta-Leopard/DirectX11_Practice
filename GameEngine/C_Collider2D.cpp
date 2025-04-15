#include "pch.h"
#include "C_Collider2D.h"

C_Collider2D::C_Collider2D()
	: C_Component(_COMPONENT_COLLIDER2D)
	, Vec2_M_ColliderScale2D{}
	, Vec3_M_ColliderScale3D{}

	, MAT_M_CollisionPosition{}

	, M_IsDependent(false)

	, M_OverLapCount(0)
{

}

C_Collider2D::C_Collider2D(const C_Collider2D& _Origin)
	: C_Component(_Origin)
	, Vec2_M_ColliderScale2D{_Origin.Vec2_M_ColliderScale2D}
	, Vec3_M_ColliderScale3D{_Origin.Vec3_M_ColliderScale3D}

	, MAT_M_CollisionPosition{_Origin .MAT_M_CollisionPosition}

	, Vec3_M_WorldMatrixDirection_s{_Origin.Vec3_M_WorldMatrixDirection_s}
	, M_IsDependent(false)

	, M_OverLapCount(0)
{

}

C_Collider2D::~C_Collider2D()
{

}

void C_Collider2D::MF_Prepare()
{
}

void C_Collider2D::MF_ComponentTick()
{
	// 스케일계산

	// 독립적인지 여부에 따라 월드공간 배율에 따른 스케일 재계산 

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
