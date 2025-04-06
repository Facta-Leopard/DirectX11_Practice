#include "pch.h"
#include "C_Collider2D.h"

C_Collider2D::C_Collider2D()
	: C_Component(_COMPONENT_COLLIDER_2D)
{

}

C_Collider2D::C_Collider2D(const C_Collider2D& _Origin)
	: C_Component(_Origin)
{

}

C_Collider2D::~C_Collider2D()
{

}

void C_Collider2D::MF_ComponentTick()
{
}
