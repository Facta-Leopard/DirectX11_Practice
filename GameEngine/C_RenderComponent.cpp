#include "pch.h"
#include "C_RenderComponent.h"

#include "C_Material.h"

C_RenderComponent::C_RenderComponent(E_COMPONENT_TYPE _E_COMPONENT)
	: C_Component(_E_COMPONENT)

	, SP_M_Mesh{}

	, SP_M_CommonMaterial{}

	, SP_M_CurrentMaterial{}
	, SP_M_CustomMaterial{}
{
}

C_RenderComponent::C_RenderComponent(const C_RenderComponent& _Origin)
	: C_Component(_Origin)

	, SP_M_Mesh{ _Origin .SP_M_Mesh}

	, SP_M_CommonMaterial{ _Origin .SP_M_CommonMaterial}

	, SP_M_CurrentMaterial{ _Origin .SP_M_CurrentMaterial}
	, SP_M_CustomMaterial{ _Origin .SP_M_CustomMaterial}		// 향후, 복사할 때 비워두는 것도 고려해보자
{
}

C_RenderComponent::~C_RenderComponent()
{
}

shared_ptr<C_Material> C_RenderComponent::MF_Get_CustomMaterial()
{
	if (nullptr == SP_M_CustomMaterial.get())					// 방어코드
	{
		shared_ptr<C_Material> SP_T_Material = shared_ptr<C_Material>(SP_M_CurrentMaterial->MF_Clone());		// 커스텀하기 위한 깊은 복사
		SP_M_CustomMaterial = SP_T_Material;
	}

	return SP_M_CustomMaterial;
}
