#include "pch.h"
#include "C_Entity.h"

C_Entity::C_Entity()
	: M_EntityID(0)
{
	UINT T_ID = C_GameEngine::SF_Get_Instance()->MF_Get_IDCount();
	M_EntityID = ++T_ID;
	C_GameEngine::SF_Get_Instance()->MF_Set_IDCount(T_ID);
}

C_Entity::C_Entity(const C_Entity& _Origin)
	: M_EntityID(0)
	, M_Name()
{
	UINT T_ID = C_GameEngine::SF_Get_Instance()->MF_Get_IDCount();
	M_EntityID = ++T_ID;
	C_GameEngine::SF_Get_Instance()->MF_Set_IDCount(T_ID);
}

C_Entity::~C_Entity()
{

}

void C_Entity::MF_Set_Name(const string& _stringName)					// Setter; M_Name
{
	wstring _wstringName = GF_ConvertStringToWString_WinAPI(_stringName);

	MF_Set_Name(_wstringName);
}