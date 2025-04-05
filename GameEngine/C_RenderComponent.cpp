#include "pch.h"
#include "C_RenderComponent.h"

C_RenderComponent::C_RenderComponent(E_COMPONENT_TYPE _E_COMPONENT)
	: C_Component(_E_COMPONENT)
{
}

C_RenderComponent::C_RenderComponent(const C_RenderComponent& _Origin)
	: C_Component(_Origin)
{
}

C_RenderComponent::~C_RenderComponent()
{
}
