#pragma once
class C_Entity
{
public:
	C_Entity();
	C_Entity(const C_Entity& _Origin);

	virtual ~C_Entity()
	{}

protected:
	UINT			M_EntityID;				// UINT
	wstring			M_Name;					// wstring

public:
	// 가상 클론함수 설정
	// 클론시 유의, 포인터로 반환하지 않으면 짤려서 복사되므로 주의
	// Component 에서도 쓰기 위해서 추상 함수화 했음
	virtual C_Entity* MF_Clone() = 0;

	UINT MF_GetEntityID()
	{
		return M_EntityID;
	}

	wstring MF_GetName()
	{
		return M_Name;
	}
};