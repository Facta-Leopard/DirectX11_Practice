#pragma once
#include "C_Entity.h"

#include "C_Object.h"

#include "global.h"

class C_Group :
	public C_Entity
{
	friend class C_Stage;
public:
	C_Group();

protected:
	C_Group(const C_Group& _Origin);

public:
	~C_Group();

protected:
	E_GROUP_INDEX                       M_GroupIndex;						// E_GROUP_NUMBER; 분류를 위한 그룹

	// Object를 관리하기 위한 Member Variable
	vector<C_Object*>                   STL_P_M_AllObject;					// vector<C_Object*>; 성능이점을 갖기위한 구조, MF_Render()를 별도로 사용하기 위함
	vector<C_Object*>                   STL_P_M_ParentObject;				// vector<C_Object*>; 최상위 부모만 관리함으로써, Transform 계산 등의 기준점을 갖기 위함

	// 재귀를 위한 너비탐색 전용 큐 자료형;
	list<C_Object*>						STL_P_M_Calculation;				// list<C_Object*>; 향후, 기존 static을 통한 정적 큐를 이용하는 설계의 구조적 문제를 개선하였으나 메모리 정리 부분은 TaskManager로 하는 것이 어떨지 생각해 볼 필요가 있음

public:
	CLONE(C_Group)

public:
	void MF_Prepare();																		  // Group 내 모든 부모 오브젝트 초기화

	void MF_Tick();																			  // Group 내 모든 부모 오브젝트 Tick() 실행

	void MF_TickAfter();																	  // Group 내 모든 부모 오브젝트 TickAfter() 실행

public:
	inline E_GROUP_INDEX MF_Set_GroupIndex()												  // Getter; E_GROUP_TYPE 관련
	{
		return M_GroupIndex;
	}

	inline void MF_Set_GroupIndex(E_GROUP_INDEX _GroupIndex)								  // Setter
	{
		M_GroupIndex = _GroupIndex;
	}

	inline vector<C_Object*> MF_Get_AllObjectFromGroup()									  // Getter; STL_M_AllObject 관련
	{
		return STL_P_M_AllObject;
	}

	inline vector<C_Object*> MF_Get_ParentObjectFromGroup()									  // Getter; STL_M_ParentObject 관련
	{
		return STL_P_M_ParentObject;
	}

	inline void MF_Attach_ObjectIntoAllObject(C_Object* _Object)							  // Attach; STL_M_AllObject 관련
	{
		STL_P_M_AllObject.push_back(_Object);
	}

	void MF_Detach_ObjectFromAllObject(C_Object* _Object);									  // Detach; 문법 유의! 벡터 계열 삭제관련 문법 유의!

	void MF_Attach_ObjectToParentObject(C_Object* _Object, bool _IsChildTogether);            // Attach; STL_M_ParentObject 관련
};