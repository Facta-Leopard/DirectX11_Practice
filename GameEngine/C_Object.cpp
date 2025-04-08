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
	, M_ParentObejct(nullptr)									// 복사해서 붙여야 할 수도 있으므로 nullptr
	, STL_M_ChildObejct{}
	, P_M_Component_s{}
	, P_M_RenderComponent(_Origin.P_M_RenderComponent)			// 기본적으로 렌더링하는 요소 복사
	, P_M_Script_s{}
{
	// 컴포넌트 깊은 복사
	for (int i = _SCRIPT_RIGID; i < _SCRIPT_END; i++)
	{
		// Colne 함수를 쓴 버전
		P_M_Component_s[i] = _Origin.P_M_Component_s[i]->MF_Clone();

		// Clone 함수를 안 쓴 버전은 사용할 수 없음
		//// 깊은 복사를 하려는 타입은 C_Component*이므로 포인터 형식인데다가,
		//// C_Component와 C_ScriptComponent가 추상클래스여서 인스턴스 생성을 할 수 없음
		//// 그러므로, new를 통합 힙 메모리 생성을 하는 깊은 복사는 원칙적으로 할 수 없음
		//// 그러나, 다형성을 이용하지 않으면 깊은 복사를 할 수 있음
		//// 상속받은 C_Component가 C_Entity를 상속받았으므로, C_Entity의 클론을 써서 깊은 복사를 해야함
		//// 불가능한 사용의 예
		//// C_ScriptComponent* T_Script = new C_ScriptComponent(_Origin.P_M_Component_s[i]);
		//// P_M_Component_s[i] = T_Script;
	}

	// 스크립트 깊은 복사
	for (int i = _SCRIPT_RIGID; i < _SCRIPT_END; i++)
	{
		P_M_Script_s[i] = _Origin.P_M_Script_s[i]->MF_Clone();
	}

	// 자식 오브젝트 깊은 복사
	for (vector<C_Object*>::iterator T_Iterator = STL_M_ChildObejct.begin(); T_Iterator < STL_M_ChildObejct.end(); T_Iterator++)
	{
		if (nullptr == *T_Iterator)			   // 방어코드; 
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
	// 기반료소부터 준비; C_Component -> C_ScriptComponent -> Obejct
	//// C_Component
	for (size_t i = 0; i < _COMPONENT_END; i++)
	{
		if (nullptr == P_M_Component_s)			// 방어코드; 
		{
			continue;
		}
		P_M_Component_s[i]->MF_Prepare();
	}

	//// C_ScriptComponent
	for (size_t i = 0; i < _COMPONENT_END; i++)
	{
		if (nullptr == P_M_Script_s)			// 방어코드; 
		{
			continue;
		}
		P_M_Script_s[i]->MF_Prepare();
	}

	//// STL_M_ChildObejct
	for (vector<C_Object*>::iterator T_Iterator = STL_M_ChildObejct.begin(); T_Iterator < STL_M_ChildObejct.end(); T_Iterator++)
	{
		if (nullptr == *T_Iterator)			   // 방어코드; 
		{
			continue;
		}
		(*T_Iterator)->MF_Prepare();
	}
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

void C_Object::MF_TickAfter()
{
	// 컴포넌트 영역
	MF_ComponentTickAfter();

	// 자식 영역
	// 죽었으면 자식객체에서 제거하는 것을 목적으로 함
	MF_Detach_DeadObjectFromChildObject();
}

void C_Object::MF_Attach_ObjectToParentObject(C_Object* _Object)
{
	if (nullptr == _Object)						// 방어코드; 들어오는 오브젝트가 nullptr일 경우 방지
	{
		POPUP_DEBUG(L"Null Pointer Dereference", L"in C_Object::MF_Attach_ObjectToParentObject(C_Object* _Object), nullptr == _Object")
		return;
	}
	MF_Detach_MyselfFromParentObject();			// 등록 전, 기존 부모에 자식 등록 상태 해제
	M_ParentObejct = _Object;

	M_ParentObejct->MF_Attach_ObjectToChildObject(this);
}

void C_Object::MF_Detach_MyselfFromParentObject()
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

void C_Object::MF_Attach_ObjectToChildObject(C_Object* _Object)
{
	if (nullptr == _Object)						// 방어코드; 들어오는 오브젝트가 nullptr일 경우 방지
	{
		POPUP_DEBUG(L"Null Pointer Dereference", L"in C_Object::MF_Attach_ObjectToParentObject(C_Object* _Object), nullptr == _Object")
			return;
	}

	// 자식오브젝트로 등록할 오브젝트의 부모오브젝트를 변경
	_Object->MF_Detach_MyselfFromParentObject();
	_Object->M_ParentObejct = this;

	// 자식오브젝트에 포함
	STL_M_ChildObejct.push_back(_Object);
}

void C_Object::MF_Detach_MyselfFromChildObject()
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

void C_Object::MF_Detach_DeadObjectFromChildObject()										// 유의! 이터레이터 erase 문법 유의!
{
	vector<C_Object*>::iterator T_Iterator = STL_M_ChildObejct.begin();					// 유의! 이터레이터 erase 문법 유의!
	for (T_Iterator = STL_M_ChildObejct.begin(); T_Iterator < STL_M_ChildObejct.end();) // 유의! 이터레이터 erase 문법 유의!
	{
		if ((*T_Iterator)->M_IsLive)													// 유의! 이터레이터 erase 문법 유의!
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
	if (nullptr == _Component)				// 방어코드
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
		if (nullptr == *T_Iterator)			// 방어코드; 
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
		if (nullptr == P_M_Component_s)			// 방어코드; 
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
		if (nullptr == P_M_Component_s)			// 방어코드; 
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
