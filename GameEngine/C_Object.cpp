#include "pch.h"
#include "C_Object.h"

C_Object::C_Object()
	: C_Entity()
	, M_GroupIndex(_GROUP_END)
	, P_M_Component_s{}
	, P_M_RenderComponent(nullptr)
	, P_M_Script_s{}
{

}

C_Object::C_Object(const C_Object& _Origin)
	: C_Entity(_Origin)
	, M_GroupIndex(_Origin.M_GroupIndex)
	, P_M_Component_s{}
	, P_M_RenderComponent(_Origin.P_M_RenderComponent)
	, P_M_Script_s{}
{
	// P_M_Script_s{} ±Ì¿∫ ∫πªÁ
	for (int i = _SCRIPT_RIGID; i < _SCRIPT_END; i++)
	{
		P_M_Script_s[i] = _Origin.P_M_Script_s[i];
	}
}

C_Object::~C_Object()
{
	DELETEALL_FIXEDARRAY_HEAP(P_M_Component_s, _COMPONENT_END)
	DELETEALL_FIXEDARRAY_HEAP(P_M_Script_s, _SCRIPT_END)
}

void C_Object::MF_Prepare()
{
}

void C_Object::MF_Tick()
{
}

void C_Object::MF_ScriptTick()
{
}

void C_Object::MF_ComponentTick()
{
}
