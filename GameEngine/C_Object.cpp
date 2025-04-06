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
	, M_ParentObejct(nullptr)									// 복사해서 붙여야 할 수도 있으므로 nullptr
	, STL_M_ChildObejct{}
	, P_M_Component_s{}
	, P_M_RenderComponent(_Origin.P_M_RenderComponent)			// 기본적으로 렌더링하는 요소 복사
	, P_M_Script_s{}
{
	// 스크립트 깊은 복사
	for (int i = _SCRIPT_RIGID; i < _SCRIPT_END; i++)
	{

	}

	// 컴포넌트 깊은 복사
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
	// 본인 영역
	MF_ScriptTick();		// 본인 소유의 스크립트 실행

	MF_ComponentTick();		// 본인 소유의 컴포넌트 실행

	// 자식 영역
	MF_ChildTick();			// 자식의 컴포넌트 실행

	// Render는 별도로 카메라 오브젝트에서 할 예정이므로 여기서는 작동시키지 않는 걸로
}

void C_Object::MF_ComponentTick()
{
	for (size_t i = 0; i < _COMPONENT_END; i++)
	{
		if (nullptr == P_M_Component_s)			// 방어코드; 
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
		if (nullptr == P_M_Script_s[i])			// 방어코드;
		{
			continue;
		}
		P_M_Script_s[i]->MF_ScriptTick();
	}
}

void C_Object::MF_Render()
{
	// 향후, C_RenderComponent 구현해야 함
	// P_M_RenderComponent->MF_Render();
}


void C_Object::MF_AttachObjectToParentObject(C_Object* _Object)
{
	if (nullptr == _Object)						// 방어코드; 들어오는 오브젝트가 nullptr일 경우 방지
	{
		POPUP_DEBUG(L"Null Pointer Dereference", L"in C_Object::MF_AttachObjectToParentObject(C_Object* _Object), nullptr == _Object")
		return;
	}
	MF_DetachMyselfFromParentObject();			// 등록 전, 기존 부모에 자식 등록 상태 해제
	M_ParentObejct = _Object;

	M_ParentObejct->MF_AttachObjectToChildObject(this);
}

void C_Object::MF_DetachMyselfFromParentObject()
{
	if (nullptr == M_ParentObejct)				// 방어코드; 부모오브젝트가 nullptr일 경우 방지
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
	if (nullptr == _Object)						// 방어코드; 들어오는 오브젝트가 nullptr일 경우 방지
	{
		POPUP_DEBUG(L"Null Pointer Dereference", L"in C_Object::MF_AttachObjectToParentObject(C_Object* _Object), nullptr == _Object")
			return;
	}

	// 자식오브젝트로 등록할 오브젝트의 부모오브젝트를 변경
	_Object->MF_DetachMyselfFromParentObject();
	_Object->M_ParentObejct = this;

	// 자식오브젝트에 포함
	STL_M_ChildObejct.push_back(_Object);
}

void C_Object::MF_DetachMyselfFromChildObject()
{
	if (STL_M_ChildObejct.empty())				// 방어코드; 자식오브젝트들이 없을 경우 방지
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
	if (nullptr == _Component)				// 방어코드
	{
		POPUP_DEBUG(L"Compnent IS nullptr", L"in C_Object::MF_AttachComponen), nullptr == _Component")
		return;
	}

// 향후, 추가구현 예정
}


void C_Object::MF_ChildTick()
{
	for (vector<C_Object*>::iterator T_Iterator = STL_M_ChildObejct.begin(); T_Iterator < STL_M_ChildObejct.end(); T_Iterator++)
	{
		if (nullptr == *T_Iterator)			// 방어코드; 
		{
			continue;
		}
		(*T_Iterator)->MF_Tick();
	}
}

