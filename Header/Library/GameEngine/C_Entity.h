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
	// 클론시 유의, 포인터로 반환하지 않으면 짤려서 복사되므로 주의
	// Component 에서도 쓰기 위해서 추상 함수화 했음
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