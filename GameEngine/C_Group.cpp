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
	if (STL_P_M_ParentObject.empty())				// ����ڵ�
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


void C_Group::MF_Detach_ObjectFromAllObject(C_Object* _Object)					// ����! ���Ϳ��� ���� �� ���� ����!
{
	if (nullptr == _Object)						// ����ڵ�
	{
		POPUP_DEBUG(L"_Object Is Nullptr", L"in C_Group::MF_Detach_ObjectFromAllObject(), nullptr == _Object")
		return;
	}

	vector<C_Object*>::iterator STL_T_Iterator = STL_P_M_AllObject.begin();		// ����! ���Ϳ��� ���� �� ���� ����!

	for (; STL_T_Iterator != STL_P_M_AllObject.end();)							// ����! ���Ϳ��� ���� �� ���� ����!
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
	if (nullptr == _Object)						// ����ڵ�
	{
		POPUP_DEBUG(L"_Object Is Nullptr", L"in C_Group::MF_Attach_ObjectToParentObject(), nullptr == _Object")
			return;
	}

	STL_P_M_ParentObject.push_back(_Object);
	_Object->M_GroupIndex = M_GroupIndex;

	// �ڽ��� �������� ���, �ڽĵ� �ش� ���̾� �Ҽ����� �����Ѵ�.
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

		// �ֻ��� �θ� ������Ʈ 
		// or �ڽĿ�����Ʈ����, �ڽı��� ���� �̵��ϱ�� �� ��� 
		// or �ֻ����θ������Ʈx, �ڽ��̵�x ���� �Ҽ��� ���� ������Ʈ�� ���
		if (nullptr == T_Object->MF_Get_ParentObject() || _IsChildTogether || T_Object->M_GroupIndex == -1)
		{
			T_Object->MF_Set_GroupIndex(M_GroupIndex);
		}
	}
}