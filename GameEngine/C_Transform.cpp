#include "pch.h"
#include "C_Transform.h"

C_Transform::C_Transform()
	: C_Component(_COMPONENT_TRANSFORM)
{
}

C_Transform::C_Transform(const C_Transform& _Origin)
	: C_Component(_Origin)
{
}

C_Transform::~C_Transform()
{
}

void C_Transform::MF_ComponentTick()
{
}
