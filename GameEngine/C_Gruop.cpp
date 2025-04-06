#include "pch.h"
#include "C_Gruop.h"

C_Group::C_Group()
	: C_Entity()
	, M_Index(_GROUP_END)
	, STL_M_AllObject{nullptr}
	, STL_M_ParentObject{nullptr}
{
}

C_Group::~C_Group()
{
}

void C_Group::MF_Prepare()
{
}

void C_Group::MF_Step()
{
	for (size_t i = 0; i < STL_M_AllObject.size(); i++)
	{
		STL_M_AllObject[i]->MF_Tick();
	}
}

void C_Group::MF_EraseObjectFromAllObject(C_Object* _Object)
{
	vector<C_Object*>::iterator STL_T_Iterator = STL_M_AllObject.begin();

	for (; STL_T_Iterator != STL_M_AllObject.end(); STL_T_Iterator++)
	{
		if (*STL_T_Iterator == _Object)
		{
			STL_M_AllObject.erase(STL_T_Iterator);
		}
	}
}

void C_Group::MF_AddObjectToParentObject(C_Object* _Object)
{

}
