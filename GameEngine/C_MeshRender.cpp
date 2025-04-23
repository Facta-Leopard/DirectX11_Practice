#include "pch.h"
#include "C_MeshRender.h"

#include "C_Transform.h"
#include "C_Material.h"
#include "C_Mesh.h"

C_MeshRender::C_MeshRender()
	: C_RenderComponent(_COMPONENT_MESH_RENDER)
{
}

C_MeshRender::C_MeshRender(const C_MeshRender& _Origin)
	: C_RenderComponent(_Origin)
{
}

C_MeshRender::~C_MeshRender()
{
}

void C_MeshRender::MF_Prepare()
{
}

void C_MeshRender::MF_ComponentTick()
{
}

void C_MeshRender::MF_ComponentTickAfter()
{
}

void C_MeshRender::MF_Render()
{
	((C_Transform*)MF_Get_OwnerObject()->MF_Get_Component(_COMPONENT_TRANSFORM))->MF_Bind_Transform();

	MF_Get_OwnerObject()->MF_Get_RenderComponent()->MF_Get_CurrentMaterial()->MF_Bind_Material();

	MF_Get_OwnerObject()->MF_Get_RenderComponent()->MF_Get_Mesh()->MF_Bind_Mesh();

}
