#include "pch.h"
#include "C_MeshRender.h"

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
