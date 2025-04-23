#include "pch.h"
#include "C_Resource.h"

C_Resource::C_Resource(E_RESOURCE_TYPE _ResourceType)
	: M_E_ResouceType(_ResourceType)
{
}

C_Resource::C_Resource(const C_Resource& _Origin)
	: M_E_ResouceType(_Origin.M_E_ResouceType)
{
}

C_Resource::~C_Resource()
{

}


