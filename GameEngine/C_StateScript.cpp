#include "pch.h"
#include "C_StateScript.h"

C_StateScript::C_StateScript()
	: C_ScriptComponent(_SCRIPT_STATE)
{
}

C_StateScript::C_StateScript(const C_StateScript& _Origin)
	: C_ScriptComponent(_Origin)
{
}

C_StateScript::~C_StateScript()
{
}

void C_StateScript::MF_ScriptTick()
{
}
