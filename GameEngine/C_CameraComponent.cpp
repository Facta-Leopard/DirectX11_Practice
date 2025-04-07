#include "pch.h"
#include "C_CameraComponent.h"

C_CameraComponent::C_CameraComponent()
	: C_Component(_COMPONENT_CAMERA)
{
}

C_CameraComponent::C_CameraComponent(const C_CameraComponent& _Origin)
	: C_Component(_Origin)
{
}

C_CameraComponent::~C_CameraComponent()
{
}

void C_CameraComponent::MF_Prepare()
{
}

void C_CameraComponent::MF_ComponentTick()
{
}
