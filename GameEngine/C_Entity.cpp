#include "pch.h"
#include "C_Entity.h"

C_Entity::C_Entity()
	: M_EntityID(0)
{
	UINT T_ID = C_GameEngine::SF_GetInstance()->MF_GetIDCount();
	M_EntityID = ++T_ID;
	C_GameEngine::SF_GetInstance()->MF_SetIDCount(T_ID);
}

C_Entity::C_Entity(const C_Entity& _Origin)
	: M_EntityID(0)
	, M_Name()
{
	UINT T_ID = C_GameEngine::SF_GetInstance()->MF_GetIDCount();
	M_EntityID = ++T_ID;
	C_GameEngine::SF_GetInstance()->MF_SetIDCount(T_ID);
}
