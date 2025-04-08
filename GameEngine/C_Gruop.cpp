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
	for (vector<C_Object*>::iterator T_Iterator = STL_M_ParentObject.begin(); T_Iterator < STL_M_ParentObject.end(); T_Iterator++)
	{
		(*T_Iterator)->MF_Prepare();
	}
}

void C_Group::MF_Tick()
{
	for (size_t i = 0; i < STL_M_AllObject.size(); i++)
	{
		STL_M_AllObject[i]->MF_Tick();
	}
}

void C_Group::MF_TickAfter()
{
	for (size_t i = 0; i < STL_M_AllObject.size(); i++)
	{
		STL_M_AllObject[i]->MF_TickAfter();
	}
}


void C_Group::MF_Detach_ObjectFromAllObject(C_Object* _Object)					// 유의! 벡터에서 지울 때 문법 주의!
{
	if (nullptr == _Object)						// 방어코드
	{
		POPUP_DEBUG(L"_Object Is Nullptr", L"in C_Group::MF_Detach_ObjectFromAllObject(), nullptr == _Object")
		return;
	}

	vector<C_Object*>::iterator STL_T_Iterator = STL_M_AllObject.begin();		// 유의! 벡터에서 지울 때 문법 주의!

	for (; STL_T_Iterator != STL_M_AllObject.end();)							// 유의! 벡터에서 지울 때 문법 주의!
	{
		if (*STL_T_Iterator == _Object)
		{
			STL_M_AllObject.erase(STL_T_Iterator);
		}
		else
		{
			STL_T_Iterator++;
		}
	}
}

void C_Group::MF_Attach_ObjectToParentObject(C_Object* _Object)
{
	if (nullptr == _Object)						// 방어코드
	{
		POPUP_DEBUG(L"_Object Is Nullptr", L"in C_Group::MF_Attach_ObjectToParentObject(), nullptr == _Object")
			return;
	}


}
