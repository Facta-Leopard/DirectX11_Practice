#include "pch.h"
#include "C_UI.h"

C_UI::C_UI()
	: M_Name()
	, M_OpenState(true)
	, P_M_ParentUI(nullptr)
	, STL_P_M_ChildUI{}
	, I_M_Vec2_ChildSize(ImVec2(0.f, 0.f))
	, M_IsFocus(false)
	, M_IsModal(false)
{
}

C_UI::~C_UI()
{
	DELETEALL_STL(STL_P_M_ChildUI)
}

HRESULT C_UI::MF_Prepare()
{
	return E_NOTIMPL;
}

void C_UI::MF_Tick()
{
	MF_UITick();							// 모듈함수를 이용한 다형성 이용

	for (auto* T_UI : STL_P_M_ChildUI)	// 유의! 오버헤드 감소를 위해, 범위기반 문으로 코드변경; 향후, 문제가 있을 시, 순회문으로 변경 필요.
	{
		if (nullptr == (T_UI))			// 방어코드
		{
			POPUP_DEBUG(L"nullptr == (T_UI)", L"in C_UI::MF_Tick(), nullptr == (T_UI)")
		}
		T_UI->MF_Tick();
	}
}

void C_UI::MF_Render()
{
	if (false == M_OpenState)				// 조기반환;
	{
		return;
	}

	if (nullptr == P_M_ParentUI)			// 부모가 없을 때; 내가 부모일 때
	{
		if (false == M_IsModal)				// 모달이 아닐 때; 계산이 자주 들어올 부분의 분기를 앞에 위치시켜 오버헤드 감소
		{
			ImGui::Begin(M_Name.c_str(), &M_OpenState);

			MF_Check_Focus();

			MF_UIRender();

			for (auto* T_UI : STL_P_M_ChildUI)	// 유의! 오버헤드 감소를 위해, 범위기반 문으로 코드변경; 향후, 문제가 있을 시, 순회문으로 변경 필요.
			{
				if (nullptr == (T_UI))			// 방어코드
				{
					POPUP_DEBUG(L"nullptr == (T_UI)", L"in C_UI::MF_Render(), nullptr == (T_UI) at State that nullptr == P_M_ParentUI, false == M_IsModal")
				}
				T_UI->MF_Render();
			}

			ImGui::End();
		}
		else								// 모달일 때;
		{
			ImGui::OpenPopup(M_Name.c_str());
			if (ImGui::BeginPopupModal(M_Name.c_str(), &M_OpenState))
			{
				MF_UIRender();

				for (auto* T_UI : STL_P_M_ChildUI)	// 유의! 오버헤드 감소를 위해, 범위기반 문으로 코드변경; 향후, 문제가 있을 시, 순회문으로 변경 필요.
				{
					if (nullptr == (T_UI))			// 방어코드
					{
						POPUP_DEBUG(L"nullptr == (T_UI)", L"in C_UI::MF_Render(), nullptr == (T_UI) at State that false == M_IsModal")
					}
					T_UI->MF_Render();
				}

				ImGui::EndPopup();
			}
		}
	}
	else									// 자식일 때
	{
		ImGui::BeginChild(M_Name.c_str(), I_M_Vec2_ChildSize);

		MF_Check_Focus();

		MF_UIRender();

		for (auto* T_UI : STL_P_M_ChildUI)	// 유의! 오버헤드 감소를 위해, 범위기반 문으로 코드변경; 향후, 문제가 있을 시, 순회문으로 변경 필요.
		{
			if (nullptr == (T_UI))			// 방어코드
			{
				POPUP_DEBUG(L"nullptr == (T_UI)", L"in C_UI::MF_Render(), nullptr == (T_UI) at State that nullptr == P_M_ParentUI")
			}
			T_UI->MF_Render();
		}

		ImGui::EndChild();

		ImGui::Separator();
	}
}

void C_UI::MF_Check_Focus()
{
	if (ImGui::IsWindowFocused(ImGuiFocusedFlags_ChildWindows))		// 유의! ImGui는 명령으로 포커싱을 잡는 WinAPI와는 달리, 계속해서 포커싱여부를 자동으로 반출!
	{
		if (false == M_IsFocus)				// 포커싱된 상태가 아니었다면
		{
			MF_Focus_On();
		}

		M_IsFocus = true;
	}
	else
	{
		if (true == M_IsFocus)
		{
			MF_Focus_Off();
		}

		M_IsFocus = false;
	}

}
