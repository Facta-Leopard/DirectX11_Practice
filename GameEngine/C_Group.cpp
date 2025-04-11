#include "pch.h"
#include "C_Group.h"
#include "C_Object.h"

C_Group::C_Group()
	: C_Entity()
	, M_GroupIndex(_GROUP_NONE)
	, STL_P_M_AllObject{}
	, STL_P_M_ParentObject{}
	, STL_P_M_Calculation{}
{
}

C_Group::C_Group(const C_Group& _Origin)
	: C_Entity(_Origin)
	, M_GroupIndex(_Origin.M_GroupIndex)
	, STL_P_M_Calculation{}
{
	for (size_t i = 0; i < _Origin.STL_P_M_ParentObject.size(); ++i)
	{
		C_Object* T_CloneObject = _Origin.STL_P_M_ParentObject[i]->MF_Clone();
		MF_Attach_ObjectToParentObject(T_CloneObject, false);
	}
}

C_Group::~C_Group()
{
	DELETEALL_STL(STL_P_M_Calculation)
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
			STL_T_Iterator = STL_P_M_AllObject.erase(STL_T_Iterator);				// 논리 로직 수정완료; 유의! Row 형식의 STL은 erase 같이 제거 해서 당기는 형식인 경우에는 이터레이터 반환되는 부분을 조심해야 함; 여기서는 이터레이터를 반환하지 않아서 다음 이터레이터로 옮겨지지 않았음;
		}
		else
		{
			++STL_T_Iterator;
		}
	}
}

void C_Group::MF_Attach_ObjectToParentObject(C_Object* _Object, bool _IsChildTogether)
{
	if (nullptr == _Object)						// 방어코드
	{
		POPUP_DEBUG(L"_Object Is Nullptr", L"in C_Group::MF_Attach_ObjectToParentObject(), nullptr == _Object")
		return;
	}

	STL_P_M_Calculation.clear();
	_Object->MF_Set_GroupIndex(M_GroupIndex);
	STL_P_M_Calculation.push_back(_Object);

	while (!STL_P_M_Calculation.empty())
	{
		C_Object* T_Object = STL_P_M_Calculation.front();
		STL_P_M_Calculation.pop_front();

		const vector<C_Object*>& T_STL_ChildObject = T_Object->MF_Get_ChildObjects();	// 향후, 깊은 복사를 해서 복사비용 오버헤드를 발생시키는 형식을 참조 형식(const type&)으로 개선하기 위해 붏어 봐야할 필요성이 있음
		for (size_t i = 0; i < T_STL_ChildObject.size(); ++i)
		{
			STL_P_M_Calculation.push_back(T_STL_ChildObject[i]);
		}

		if (nullptr == T_Object->MF_Get_ParentObject() || _IsChildTogether || T_Object->MF_Get_GroupIndex() == _GROUP_NONE)
		{
			T_Object->MF_Set_GroupIndex(M_GroupIndex);
		}
	}
}