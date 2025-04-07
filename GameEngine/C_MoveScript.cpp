#include "pch.h"
#include "C_MoveScript.h"

C_MoveScript::C_MoveScript()
	: C_ScriptComponent(_SCRIPT_MOVE)
{
}

C_MoveScript::C_MoveScript(const C_MoveScript& _Origin)
	: C_ScriptComponent(_Origin)
{
}

C_MoveScript::~C_MoveScript()
{
}

void C_MoveScript::MF_Prepare()
{
}

void C_MoveScript::MF_ScriptTick()
{
}
