#include "pch.h"
#include "C_RigidScript.h"

C_RigidScript::C_RigidScript()
	: C_ScriptComponent(_SCRIPT_RIGID)
{
}

C_RigidScript::C_RigidScript(const C_RigidScript& _Origin)
	:C_ScriptComponent(_Origin)
{
}

C_RigidScript::~C_RigidScript()
{
}

void C_RigidScript::MF_ScriptTick()
{
}
