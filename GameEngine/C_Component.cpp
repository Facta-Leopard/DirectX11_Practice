#include "pch.h"
#include "C_Component.h"

C_Component::C_Component(E_COMPONENT_TYPE _E_COMPONENT)
	: L_M_ComponentType(_E_COMPONENT)
	, P_M_OwnerObject(nullptr)
{

}

C_Component::C_Component(const C_Component& _Origin)
	: C_Entity(_Origin)
	, L_M_ComponentType(_Origin.L_M_ComponentType)
	, P_M_OwnerObject(nullptr)						// ������ ���� ��ü�� ���� ������ �� ���縦 �� �ϴ°��� ���Ͽ� �ٽ� �� �� �����غ���..
{

}

C_Component::~C_Component()
{

}
