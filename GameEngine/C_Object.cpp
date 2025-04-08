#include "pch.h"
#include "C_Object.h"

C_Object::C_Object()
	: C_Entity()
	, M_GroupType(_GROUP_END)
	, M_IsLive(true)
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
	, M_IsLive(_Origin.M_IsLive)
	, M_ParentObejct(nullptr)									// �����ؼ� �ٿ��� �� ���� �����Ƿ� nullptr
	, STL_M_ChildObejct{}
	, P_M_Component_s{}
	, P_M_RenderComponent(_Origin.P_M_RenderComponent)			// �⺻������ �������ϴ� ��� ����
	, P_M_Script_s{}
{
	// ������Ʈ ���� ����
	for (int i = _SCRIPT_RIGID; i < _SCRIPT_END; i++)
	{
		// Colne �Լ��� �� ����
		P_M_Component_s[i] = _Origin.P_M_Component_s[i]->MF_Clone();

		// Clone �Լ��� �� �� ������ ����� �� ����
		//// ���� ���縦 �Ϸ��� Ÿ���� C_Component*�̹Ƿ� ������ �����ε��ٰ�,
		//// C_Component�� C_ScriptComponent�� �߻�Ŭ�������� �ν��Ͻ� ������ �� �� ����
		//// �׷��Ƿ�, new�� ���� �� �޸� ������ �ϴ� ���� ����� ��Ģ������ �� �� ����
		//// �׷���, �������� �̿����� ������ ���� ���縦 �� �� ����
		//// ��ӹ��� C_Component�� C_Entity�� ��ӹ޾����Ƿ�, C_Entity�� Ŭ���� �Ἥ ���� ���縦 �ؾ���
		//// �Ұ����� ����� ��
		//// C_ScriptComponent* T_Script = new C_ScriptComponent(_Origin.P_M_Component_s[i]);
		//// P_M_Component_s[i] = T_Script;
	}

	// ��ũ��Ʈ ���� ����
	for (int i = _SCRIPT_RIGID; i < _SCRIPT_END; i++)
	{
		P_M_Script_s[i] = _Origin.P_M_Script_s[i]->MF_Clone();
	}

	// �ڽ� ������Ʈ ���� ����
	for (vector<C_Object*>::iterator T_Iterator = STL_M_ChildObejct.begin(); T_Iterator < STL_M_ChildObejct.end(); T_Iterator++)
	{
		if (nullptr == *T_Iterator)			   // ����ڵ�; 
		{
			continue;
		}
		
		C_Object* T_Object = (*T_Iterator)->MF_Clone();

		STL_M_ChildObejct.push_back(T_Object);
	}
}

C_Object::~C_Object()
{
	DELETEALL_FIXEDARRAY_HEAP(P_M_Component_s, _COMPONENT_END)
	DELETEALL_FIXEDARRAY_HEAP(P_M_Script_s, _SCRIPT_END)
	DELETEALL_STL(STL_M_ChildObejct)
}

void C_Object::MF_Prepare()
{
	// ��ݷ�Һ��� �غ�; C_Component -> C_ScriptComponent -> Obejct
	//// C_Component
	for (size_t i = 0; i < _COMPONENT_END; i++)
	{
		if (nullptr == P_M_Component_s)			// ����ڵ�; 
		{
			continue;
		}
		P_M_Component_s[i]->MF_Prepare();
	}

	//// C_ScriptComponent
	for (size_t i = 0; i < _COMPONENT_END; i++)
	{
		if (nullptr == P_M_Script_s)			// ����ڵ�; 
		{
			continue;
		}
		P_M_Script_s[i]->MF_Prepare();
	}

	//// STL_M_ChildObejct
	for (vector<C_Object*>::iterator T_Iterator = STL_M_ChildObejct.begin(); T_Iterator < STL_M_ChildObejct.end(); T_Iterator++)
	{
		if (nullptr == *T_Iterator)			   // ����ڵ�; 
		{
			continue;
		}
		(*T_Iterator)->MF_Prepare();
	}
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

void C_Object::MF_TickAfter()
{
	// ������Ʈ ����
	MF_ComponentTickAfter();

	// �ڽ� ����
	// �׾����� �ڽİ�ü���� �����ϴ� ���� �������� ��
	MF_Detach_DeadObjectFromChildObject();
}

void C_Object::MF_Attach_ObjectToParentObject(C_Object* _Object)
{
	if (nullptr == _Object)						// ����ڵ�; ������ ������Ʈ�� nullptr�� ��� ����
	{
		POPUP_DEBUG(L"Null Pointer Dereference", L"in C_Object::MF_Attach_ObjectToParentObject(C_Object* _Object), nullptr == _Object")
		return;
	}
	MF_Detach_MyselfFromParentObject();			// ��� ��, ���� �θ� �ڽ� ��� ���� ����
	M_ParentObejct = _Object;

	M_ParentObejct->MF_Attach_ObjectToChildObject(this);
}

void C_Object::MF_Detach_MyselfFromParentObject()
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

void C_Object::MF_Attach_ObjectToChildObject(C_Object* _Object)
{
	if (nullptr == _Object)						// ����ڵ�; ������ ������Ʈ�� nullptr�� ��� ����
	{
		POPUP_DEBUG(L"Null Pointer Dereference", L"in C_Object::MF_Attach_ObjectToParentObject(C_Object* _Object), nullptr == _Object")
			return;
	}

	// �ڽĿ�����Ʈ�� ����� ������Ʈ�� �θ������Ʈ�� ����
	_Object->MF_Detach_MyselfFromParentObject();
	_Object->M_ParentObejct = this;

	// �ڽĿ�����Ʈ�� ����
	STL_M_ChildObejct.push_back(_Object);
}

void C_Object::MF_Detach_MyselfFromChildObject()
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

void C_Object::MF_Detach_DeadObjectFromChildObject()										// ����! ���ͷ����� erase ���� ����!
{
	vector<C_Object*>::iterator T_Iterator = STL_M_ChildObejct.begin();					// ����! ���ͷ����� erase ���� ����!
	for (T_Iterator = STL_M_ChildObejct.begin(); T_Iterator < STL_M_ChildObejct.end();) // ����! ���ͷ����� erase ���� ����!
	{
		if ((*T_Iterator)->M_IsLive)													// ����! ���ͷ����� erase ���� ����!
		{
			++T_Iterator;
		}
		else
		{
			STL_M_ChildObejct.erase(T_Iterator);
		}
	}
}

void C_Object::MF_Attach_Component(C_Component* _Component)
{
	if (nullptr == _Component)				// ����ڵ�
	{
		POPUP_DEBUG(L"Compnent IS nullptr", L"in C_Object::MF_Attach_Componen), nullptr == _Component")
		return;
	}

	E_COMPONENT_TYPE T_COMPONENT_TYPE = _Component->MF_Get_ComponentType();

	P_M_Component_s[T_COMPONENT_TYPE] = _Component;
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

void C_Object::MF_ComponentTickAfter()
{
	for (size_t i = 0; i < _COMPONENT_END; i++)
	{
		if (nullptr == P_M_Component_s)			// ����ڵ�; 
		{
			continue;
		}
		P_M_Component_s[i]->MF_ComponentTickAfter();
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
