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
	E_GROUP_INDEX                       M_GroupIndex;						// E_GROUP_NUMBER; �з��� ���� �׷�

	// Object�� �����ϱ� ���� Member Variable
	vector<C_Object*>                   STL_P_M_AllObject;					// vector<C_Object*>; ���������� �������� ����, MF_Render()�� ������ ����ϱ� ����
	vector<C_Object*>                   STL_P_M_ParentObject;				// vector<C_Object*>; �ֻ��� �θ� ���������ν�, Transform ��� ���� �������� ���� ����

	// ��͸� ���� �ʺ�Ž�� ���� ť �ڷ���;
	list<C_Object*>						STL_P_M_Calculation;				// list<C_Object*>; ����, ���� static�� ���� ���� ť�� �̿��ϴ� ������ ������ ������ �����Ͽ����� �޸� ���� �κ��� TaskManager�� �ϴ� ���� ��� ������ �� �ʿ䰡 ����

public:
	CLONE(C_Group)

public:
	void MF_Prepare();																		  // Group �� ��� �θ� ������Ʈ �ʱ�ȭ

	void MF_Tick();																			  // Group �� ��� �θ� ������Ʈ Tick() ����

	void MF_TickAfter();																	  // Group �� ��� �θ� ������Ʈ TickAfter() ����

public:
	inline E_GROUP_INDEX MF_Set_GroupIndex()												  // Getter; E_GROUP_TYPE ����
	{
		return M_GroupIndex;
	}

	inline void MF_Set_GroupIndex(E_GROUP_INDEX _GroupIndex)								  // Setter
	{
		M_GroupIndex = _GroupIndex;
	}

	inline vector<C_Object*> MF_Get_AllObjectFromGroup()									  // Getter; STL_M_AllObject ����
	{
		return STL_P_M_AllObject;
	}

	inline vector<C_Object*> MF_Get_ParentObjectFromGroup()									  // Getter; STL_M_ParentObject ����
	{
		return STL_P_M_ParentObject;
	}

	inline void MF_Attach_ObjectIntoAllObject(C_Object* _Object)							  // Attach; STL_M_AllObject ����
	{
		STL_P_M_AllObject.push_back(_Object);
	}

	void MF_Detach_ObjectFromAllObject(C_Object* _Object);									  // Detach; ���� ����! ���� �迭 �������� ���� ����!

	void MF_Attach_ObjectToParentObject(C_Object* _Object, bool _IsChildTogether);            // Attach; STL_M_ParentObject ����
};