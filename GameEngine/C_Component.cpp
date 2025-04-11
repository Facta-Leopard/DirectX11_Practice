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
	, P_M_OwnerObject(nullptr)						// 본인이 속한 객체에 대한 정보는 왜 복사를 안 하는가에 대하여 다시 한 번 생각해보자..
{
}

C_Component::~C_Component()
{
	// 향후, 상호참조 문제는 없을 것으로 보이나 메모리 누수가 있는지 테스트 해보는 게 좋을 듯
	// 만약, 있다면 P_M_OwnerObject == nullptr 로직 등을 추가하자
}
