#include "pch.h"
#include "C_ScriptComponent.h"

C_ScriptComponent::C_ScriptComponent(E_SCRIPT_TYPE _ScrptType)
	: C_Component(_COMPONENT_SCRIPT)
	, M_ScrptType(_ScrptType)
{
}

C_ScriptComponent::C_ScriptComponent(const C_ScriptComponent& _Origin)
	: C_Component(_COMPONENT_SCRIPT)
{
}

C_ScriptComponent::~C_ScriptComponent()
{
}
