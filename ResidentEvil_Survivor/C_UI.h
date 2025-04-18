#pragma once

#include "IMGUI/imgui.h"

#include "GameEngine/global.h"

class C_UI
{
public:
	C_UI();

public:
	~C_UI();


protected:
	string				M_Name;						// string; IMGUI�� wstring�� �������� ����
	bool				M_IsActive;					// bool; Ȱ��ȭ ����

	C_UI*				P_M_ParentUI;				// C_UI*; �θ� UI
	vector<C_UI*>		STL_P_M_ChildUI;			// vector<C_UI*>; �ڽ� UI��

	ImVec2				I_M_Vec2_ChildSize;			// ImVec2;

	bool				M_IsFocus;					// bool;
	bool				M_IsModal;					// bool; ���۰����� ��޼������� ����

public:	
	// Tick ����
	virtual void MF_Tick();							// �����Լ� ����
	virtual void MF_UITick() {}						// �����׼� ����; ����Լ�

	// Render ����
	virtual void MF_Render();						// �����Լ� ����
	virtual void MF_UIRender() {}						// �����Լ� ����; ����Լ�

	virtual void MF_Focus_On() {}						// �����Լ� ����; ����Լ�
	virtual void MF_Focus_Off() {}					// �����Լ� ����; ����Լ�

public:
	virtual HRESULT MF_Prepare();					// �����Լ� ����; �ʱ�ȭ�Լ�

	void MF_Check_Focus();							// ��Ŀ�� ���� üũ

	inline void MF_Set_Active(bool _Active)		// Setter; true
	{
		if (M_IsActive == _Active)				// �����ȯ; ������� ���̱�
		{
			return;
		}

		M_IsActive = _Active;

		if (true == _Active)
		{
			MF_Set_ActivateOn();
		}
		else
		{
			MF_Set_ActivateOff();
		}
	}

	inline void MF_Set_ActivateOn()				// Setter; true
	{
		M_IsActive = true;
	}

	inline void MF_Set_ActivateOff()			// Setter; false
	{
		M_IsActive = false;
	}

	ImVec2 MF_Get_ChildSize()					// Getter; I_M_Vec2_ChildSize
	{
		return I_M_Vec2_ChildSize;
	}

	inline void MF_Set_ChildSize(ImVec2 _I_Vec2_Size)	// Setter;
	{
		I_M_Vec2_ChildSize = _I_Vec2_Size;
	}
};