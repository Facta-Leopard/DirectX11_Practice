#include "pch.h"
#include "C_FSMScript.h"

C_FSMScript::C_FSMScript()
	: C_ScriptComponent(_SCRIPT_NPC)
{
}

C_FSMScript::C_FSMScript(const C_FSMScript& _Origin)
	: C_ScriptComponent(_Origin)
{
}

C_FSMScript::~C_FSMScript()
{
}

void C_FSMScript::MF_ScriptTick()
{
}
