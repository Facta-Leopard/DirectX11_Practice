#pragma once

#include <string>
using namespace std;
#include "globalFunction.h"

class C_Entity
{
public:
	C_Entity();

protected:
	C_Entity(const C_Entity& _Origin);

public:
	virtual ~C_Entity();

protected:
	UINT			M_EntityID;				// UINT
	wstring			M_Name;					// wstring

public:
	// Ŭ�н� ����, �����ͷ� ��ȯ���� ������ ©���� ����ǹǷ� ����
	// Component ������ ���� ���ؼ� �߻� �Լ�ȭ ����
	virtual C_Entity* MF_Clone() = 0;									// Clone Function; Virtual

public:
	inline UINT MF_Get_EntityID()										// Getter; M_EntityID
	{
		return M_EntityID;
	}

	inline wstring MF_Get_Name()										// Getter; M_Name
	{
		return M_Name;
	}

public:
	inline void MF_Set_Name(const wstring& _wstringName)				// Setter; M_Name
	{
		M_Name = _wstringName;
	}

	void MF_Set_Name(const string& _stringName);						// Setter; M_Name
};