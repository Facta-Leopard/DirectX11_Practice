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
	// ���� Ŭ���Լ� ����
	// Ŭ�н� ����, �����ͷ� ��ȯ���� ������ ©���� ����ǹǷ� ����
	// Component ������ ���� ���ؼ� �߻� �Լ�ȭ ����
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