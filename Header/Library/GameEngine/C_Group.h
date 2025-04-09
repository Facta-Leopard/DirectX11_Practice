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
	E_GROUP_TYPE                        M_GroupIndex;               // E_GROUP_NUMBER; �з��� ���� �׷�

	// Object�� �����ϱ� ���� Member Variable
	vector<C_Object*>                   STL_P_M_AllObject;            // vector<C_Object*>; ���������� �������� ����, MF_Render()�� ������ ����ϱ� ����
	vector<C_Object*>                   STL_P_M_ParentObject;         // vector<C_Object*>; �ֻ��� �θ� ���������ν�, Transform ��� ���� �������� ���� ����


public:
	CLONE(C_Group)

public:
	void MF_Prepare();                                                   // Group �� ��� �θ� ������Ʈ �ʱ�ȭ

	void MF_Tick();                                                      // Group �� ��� �θ� ������Ʈ Tick() ����

	void MF_TickAfter();                                                 // Group �� ��� �θ� ������Ʈ TickAfter() ����

	// STL_M_AllObject ����
	inline void MF_Insert_ObjectIntoAllObject(C_Object* _Object)
	{
		STL_P_M_AllObject.push_back(_Object);
	}

	// E_GROUP_TYPE ����
	inline void MF_Set_GroupIndex(E_GROUP_TYPE _GroupIndex)                   // Setter
	{
		M_GroupIndex = _GroupIndex;
	}

	inline vector<C_Object*> MF_Get_AllObjectFromGroup()                 // Getter
	{
		return STL_P_M_AllObject;
	}

	// STL_M_ParentObject ����
	inline vector<C_Object*> MF_Get_ParentObjectFromGroup()              // Getter
	{
		return STL_P_M_ParentObject;
	}

	// STL_M_AllObject ����
	void MF_Detach_ObjectFromAllObject(C_Object* _Object);               // Detach; ���� ����! ���� �迭 �������� ���� ����!

	// STL_M_ParentObject ����
	void MF_Attach_ObjectToParentObjects(C_Object* _Object, bool _IsChildTogether);              // Attach; 
};