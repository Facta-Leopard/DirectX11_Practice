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
	string				M_Name;						// string; IMGUI는 wstring을 지원하지 않음
	bool				M_IsActive;					// bool; 활성화 여부

	C_UI*				P_M_ParentUI;				// C_UI*; 부모 UI
	vector<C_UI*>		STL_P_M_ChildUI;			// vector<C_UI*>; 자식 UI들

	ImVec2				I_M_Vec2_ChildSize;			// ImVec2;

	bool				M_IsFocus;					// bool;
	bool				M_IsModal;					// bool; 조작가능한 모달성격인지 여부

public:	
	// Tick 관련
	virtual void MF_Tick();							// 가상함수 설정
	virtual void MF_UITick() {}						// 가상항수 설정; 모듈함수

	// Render 관련
	virtual void MF_Render();						// 가상함수 설정
	virtual void MF_UIRender() {}						// 가상함수 설정; 모듈함수

	virtual void MF_Focus_On() {}						// 가상함수 설정; 모듈함수
	virtual void MF_Focus_Off() {}					// 가상함수 설정; 모듈함수

public:
	virtual HRESULT MF_Prepare();					// 가상함수 설정; 초기화함수

	void MF_Check_Focus();							// 포커싱 여부 체크

	inline void MF_Set_Active(bool _Active)		// Setter; true
	{
		if (M_IsActive == _Active)				// 조기반환; 오버헤드 줄이기
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