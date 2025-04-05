#include "pch.h"
#include "C_Object.h"

C_Object::C_Object()
	: C_Entity()
	, P_M_Component_s{}
	, P_M_RenderComponent(nullptr)
	, P_M_Script_s{}
{

}

C_Object::C_Object(const C_Object& _Origin)
	: C_Entity(_Origin)
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
	DELETE_FIXEDARRAY_HEAP(P_M_Component_s, _COMPONENT_END)
	DELETE_FIXEDARRAY_HEAP(P_M_Script_s, _SCRIPT_END)
}
