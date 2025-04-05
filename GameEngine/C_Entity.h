#pragma once
class C_Entity
{
public:
	C_Entity();
	C_Entity(const C_Entity& _Origin);

	virtual ~C_Entity();

protected:
	UINT			M_EntityID;				// UINT
	wstring			M_Name;					// wstring

public:
	// Ŭ�н� ����, �����ͷ� ��ȯ���� ������ ©���� ����ǹǷ� ����
	// Component ������ ���� ���ؼ� �߻� �Լ�ȭ ����
	virtual C_Entity* MF_Clone() = 0;		// Clone Function; Virtual


	inline UINT MF_GetEntityID()			// Getter; M_EntityID
	{
		return M_EntityID;
	}

	inline wstring MF_GetName()				// Getter; M_Name
	{
		return M_Name;
	}
};