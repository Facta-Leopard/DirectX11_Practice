#include "pch.h"
#include "C_Light2D.h"

C_Light2D::C_Light2D()
	: C_Component(_COMPONENT_LIGHT_2D)
{

}

C_Light2D::C_Light2D(const C_Light2D& _Origin)
	: C_Component(_Origin)
{

}

C_Light2D::~C_Light2D()
{

}

void C_Light2D::MF_ComponentTick()
{
}
