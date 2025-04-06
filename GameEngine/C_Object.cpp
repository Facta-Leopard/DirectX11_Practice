#include "pch.h"
#include "C_Object.h"

C_Object::C_Object()
	: C_Entity()
	, M_GroupType(_GROUP_END)
	, M_IsDead(false)
	, M_ParentObejct(nullptr)
	, STL_M_ChildObejct{}
	, P_M_Component_s{}
	, P_M_RenderComponent(nullptr)
	, P_M_Script_s{}
{

}

C_Object::C_Object(const C_Object& _Origin)
	: C_Entity(_Origin)
	, M_GroupType(_Origin.M_GroupType)
	, M_IsDead(_Origin.M_IsDead)
	, M_ParentObejct(nullptr)									// �����ؼ� �ٿ��� �� ���� �����Ƿ� nullptr
	, STL_M_ChildObejct{}
	, P_M_Component_s{}
	, P_M_RenderComponent(_Origin.P_M_RenderComponent)			// �⺻������ �������ϴ� ��� ����
	, P_M_Script_s{}
{
	// ��ũ��Ʈ ���� ����
	for (int i = _SCRIPT_RIGID; i < _SCRIPT_END; i++)
	{

	}

	// ������Ʈ ���� ����
	for (int i = _SCRIPT_RIGID; i < _SCRIPT_END; i++)
	{

	}

}

C_Object::~C_Object()
{
	DELETEALL_FIXEDARRAY_HEAP(P_M_Component_s, _COMPONENT_END)
	DELETEALL_FIXEDARRAY_HEAP(P_M_Script_s, _SCRIPT_END)
}

void C_Object::MF_Prepare()
{
}

void C_Object::MF_Tick()
{
	// ���� ����
	MF_ScriptTick();		// ���� ������ ��ũ��Ʈ ����

	MF_ComponentTick();		// ���� ������ ������Ʈ ����

	// �ڽ� ����
	MF_ChildTick();			// �ڽ��� ������Ʈ ����

	// Render�� ������ ī�޶� ������Ʈ���� �� �����̹Ƿ� ���⼭�� �۵���Ű�� �ʴ� �ɷ�
}

void C_Object::MF_ComponentTick()
{
	for (size_t i = 0; i < _COMPONENT_END; i++)
	{
		if (nullptr == P_M_Component_s)			// ����ڵ�; 
		{
			continue;
		}
		P_M_Component_s[i]->MF_ComponentTick();
	}
}

void C_Object::MF_ScriptTick()
{
	for (size_t i = 0; i < _SCRIPT_END; i++)
	{
		if (nullptr == P_M_Script_s[i])			// ����ڵ�;
		{
			continue;
		}
		P_M_Script_s[i]->MF_ScriptTick();
	}
}

void C_Object::MF_Render()
{
	// ����, C_RenderComponent �����ؾ� ��
	// P_M_RenderComponent->MF_Render();
}


void C_Object::MF_AttachObjectToParentObject(C_Object* _Object)
{
	if (nullptr == _Object)						// ����ڵ�; ������ ������Ʈ�� nullptr�� ��� ����
	{
		POPUP_DEBUG(L"Null Pointer Dereference", L"in C_Object::MF_AttachObjectToParentObject(C_Object* _Object), nullptr == _Object")
		return;
	}
	MF_DetachMyselfFromParentObject();			// ��� ��, ���� �θ� �ڽ� ��� ���� ����
	M_ParentObejct = _Object;

	M_ParentObejct->MF_AttachObjectToChildObject(this);
}

void C_Object::MF_DetachMyselfFromParentObject()
{
	if (nullptr == M_ParentObejct)				// ����ڵ�; �θ������Ʈ�� nullptr�� ��� ����
	{
		return;
	}

	vector<C_Object*> STL_T_ChildObject = M_ParentObejct->STL_M_ChildObejct;

	for (vector<C_Object*>::iterator T_Iterator = STL_T_ChildObject.begin(); T_Iterator < STL_T_ChildObject.end(); T_Iterator++)
	{
		if (*T_Iterator == this)
		{
			STL_T_ChildObject.erase(T_Iterator);

			M_ParentObejct = nullptr;
		}
	}
}


void C_Object::MF_AttachObjectToChildObject(C_Object* _Object)
{
	if (nullptr == _Object)						// ����ڵ�; ������ ������Ʈ�� nullptr�� ��� ����
	{
		POPUP_DEBUG(L"Null Pointer Dereference", L"in C_Object::MF_AttachObjectToParentObject(C_Object* _Object), nullptr == _Object")
			return;
	}

	// �ڽĿ�����Ʈ�� ����� ������Ʈ�� �θ������Ʈ�� ����
	_Object->MF_DetachMyselfFromParentObject();
	_Object->M_ParentObejct = this;

	// �ڽĿ�����Ʈ�� ����
	STL_M_ChildObejct.push_back(_Object);
}

void C_Object::MF_DetachMyselfFromChildObject()
{
	if (STL_M_ChildObejct.empty())				// ����ڵ�; �ڽĿ�����Ʈ���� ���� ��� ����
	{
			return;
	}

	vector<C_Object*> STL_T_ChildObject = M_ParentObejct->STL_M_ChildObejct;

	for (vector<C_Object*>::iterator T_Iterator = STL_T_ChildObject.begin(); T_Iterator < STL_T_ChildObject.end(); T_Iterator++)
	{
		if (*T_Iterator == this)
		{
			STL_T_ChildObject.erase(T_Iterator);

			M_ParentObejct = nullptr;
		}
	}
}

void C_Object::MF_AttachComponent(C_Component* _Component)
{
	if (nullptr == _Component)				// ����ڵ�
	{
		POPUP_DEBUG(L"Compnent IS nullptr", L"in C_Object::MF_AttachComponen), nullptr == _Component")
		return;
	}

// ����, �߰����� ����
}


void C_Object::MF_ChildTick()
{
	for (vector<C_Object*>::iterator T_Iterator = STL_M_ChildObejct.begin(); T_Iterator < STL_M_ChildObejct.end(); T_Iterator++)
	{
		if (nullptr == *T_Iterator)			// ����ڵ�; 
		{
			continue;
		}
		(*T_Iterator)->MF_Tick();
	}
}

