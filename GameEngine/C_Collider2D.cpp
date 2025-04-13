#include "pch.h"
#include "C_Collider2D.h"

C_Collider2D::C_Collider2D()
	: C_Component(_COMPONENT_COLLIDER_2D)
	, Vec2_M_ColliderScale2D{}
	, Vec3_M_ColliderScale3D{}

	, Mat_M_CollisionPosition{}

	, M_IsCollision(false)

	, M_OverLapCount(0)
{

}

C_Collider2D::C_Collider2D(const C_Collider2D& _Origin)
	: C_Component(_Origin)
	, Vec2_M_ColliderScale2D{_Origin.Vec2_M_ColliderScale2D}
	, Vec3_M_ColliderScale3D{_Origin.Vec3_M_ColliderScale3D}

	, Mat_M_CollisionPosition{ _Origin .Mat_M_CollisionPosition}

	, M_IsCollision(false)

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


	// 최종
}

void C_Collider2D::MF_ComponentTickAfter()
{
}
