#include "pch.h"
#include "C_Group.h"
#include "C_Object.h"

C_Group::C_Group()
	: C_Entity()
	, M_GroupIndex(_GROUP_END)
	, STL_P_M_AllObject{}
	, STL_P_M_ParentObject{}
{
}

C_Group::C_Group(const C_Group& _Origin)
	: C_Entity(_Origin)
	, M_GroupIndex(_Origin.M_GroupIndex)
{
	for (size_t i = 0; i < _Origin.STL_P_M_ParentObject.size(); ++i)
	{
		C_Object* T_CloneObject = _Origin.STL_P_M_ParentObject[i]->MF_Clone();
		MF_Attach_ObjectToParentObjects(T_CloneObject, false);
	}
}

C_Group::~C_Group()
{
}

void C_Group::MF_Prepare()
{
	if (STL_P_M_ParentObject.empty())				// 방어코드
	{
		POPUP_DEBUG(L"STL_M_ParentObject.empty()", L"in C_Group::MF_Prepare(), STL_M_ParentObject.empty()")
		return;
	}
	for (vector<C_Object*>::iterator T_Iterator = STL_P_M_ParentObject.begin(); T_Iterator < STL_P_M_ParentObject.end(); T_Iterator++)
	{
		(*T_Iterator)->MF_Prepare();
	}
}

void C_Group::MF_Tick()
{
	for (size_t i = 0; i < STL_P_M_AllObject.size(); i++)
	{
		STL_P_M_AllObject[i]->MF_Tick();
	}
}

void C_Group::MF_TickAfter()
{
	for (size_t i = 0; i < STL_P_M_AllObject.size(); i++)
	{
		STL_P_M_AllObject[i]->MF_TickAfter();
	}
}


void C_Group::MF_Detach_ObjectFromAllObject(C_Object* _Object)					// 유의! 벡터에서 지울 때 문법 주의!
{
	if (nullptr == _Object)						// 방어코드
	{
		POPUP_DEBUG(L"_Object Is Nullptr", L"in C_Group::MF_Detach_ObjectFromAllObject(), nullptr == _Object")
		return;
	}

	vector<C_Object*>::iterator STL_T_Iterator = STL_P_M_AllObject.begin();		// 유의! 벡터에서 지울 때 문법 주의!

	for (; STL_T_Iterator != STL_P_M_AllObject.end();)							// 유의! 벡터에서 지울 때 문법 주의!
	{
		if (*STL_T_Iterator == _Object)
		{
			STL_P_M_AllObject.erase(STL_T_Iterator);
		}
		else
		{
			++STL_T_Iterator;
		}
	}
}

void C_Group::MF_Attach_ObjectToParentObjects(C_Object* _Object, bool _IsChildTogether)
{
	if (nullptr == _Object)						// 방어코드
	{
		POPUP_DEBUG(L"_Object Is Nullptr", L"in C_Group::MF_Attach_ObjectToParentObject(), nullptr == _Object")
			return;
	}

	STL_P_M_ParentObject.push_back(_Object);
	_Object->M_GroupIndex = M_GroupIndex;

	// 자식을 보유했을 경우, 자식도 해당 레이어 소속으로 변경한다.
	static list<C_Object*> T_Queue;
	T_Queue.clear();
	T_Queue.push_back(_Object);

	while (!T_Queue.empty())
	{
		C_Object* T_Object = T_Queue.front();
		T_Queue.pop_front();

		const vector<C_Object*>& T_STL_ChildObject = T_Object->MF_Get_ChildObjects();
		for (size_t i = 0; i < T_STL_ChildObject.size(); ++i)
		{
			T_Queue.push_back(T_STL_ChildObject[i]);
		}

		// 최상위 부모 오브젝트 
		// or 자식오브젝트여도, 자식까지 같이 이동하기로 한 경우 
		// or 최상위부모오브젝트x, 자식이동x 더라도 소속이 없는 오브젝트인 경우
		if (nullptr == T_Object->MF_Get_ParentObject() || _IsChildTogether || T_Object->M_GroupIndex == -1)
		{
			T_Object->MF_Set_GroupIndex(M_GroupIndex);
		}
	}
}