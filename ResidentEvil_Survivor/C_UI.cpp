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
	MF_UITick();							// ����Լ��� �̿��� ������ �̿�

	for (auto* T_UI : STL_P_M_ChildUI)	// ����! ������� ���Ҹ� ����, ������� ������ �ڵ庯��; ����, ������ ���� ��, ��ȸ������ ���� �ʿ�.
	{
		if (nullptr == (T_UI))			// ����ڵ�
		{
			POPUP_DEBUG(L"nullptr == (T_UI)", L"in C_UI::MF_Tick(), nullptr == (T_UI)")
		}
		T_UI->MF_Tick();
	}
}

void C_UI::MF_Render()
{
	if (false == M_OpenState)				// �����ȯ;
	{
		return;
	}

	if (nullptr == P_M_ParentUI)			// �θ� ���� ��; ���� �θ��� ��
	{
		if (false == M_IsModal)				// ����� �ƴ� ��; ����� ���� ���� �κ��� �б⸦ �տ� ��ġ���� ������� ����
		{
			ImGui::Begin(M_Name.c_str(), &M_OpenState);

			MF_Check_Focus();

			MF_UIRender();

			for (auto* T_UI : STL_P_M_ChildUI)	// ����! ������� ���Ҹ� ����, ������� ������ �ڵ庯��; ����, ������ ���� ��, ��ȸ������ ���� �ʿ�.
			{
				if (nullptr == (T_UI))			// ����ڵ�
				{
					POPUP_DEBUG(L"nullptr == (T_UI)", L"in C_UI::MF_Render(), nullptr == (T_UI) at State that nullptr == P_M_ParentUI, false == M_IsModal")
				}
				T_UI->MF_Render();
			}

			ImGui::End();
		}
		else								// ����� ��;
		{
			ImGui::OpenPopup(M_Name.c_str());
			if (ImGui::BeginPopupModal(M_Name.c_str(), &M_OpenState))
			{
				MF_UIRender();

				for (auto* T_UI : STL_P_M_ChildUI)	// ����! ������� ���Ҹ� ����, ������� ������ �ڵ庯��; ����, ������ ���� ��, ��ȸ������ ���� �ʿ�.
				{
					if (nullptr == (T_UI))			// ����ڵ�
					{
						POPUP_DEBUG(L"nullptr == (T_UI)", L"in C_UI::MF_Render(), nullptr == (T_UI) at State that false == M_IsModal")
					}
					T_UI->MF_Render();
				}

				ImGui::EndPopup();
			}
		}
	}
	else									// �ڽ��� ��
	{
		ImGui::BeginChild(M_Name.c_str(), I_M_Vec2_ChildSize);

		MF_Check_Focus();

		MF_UIRender();

		for (auto* T_UI : STL_P_M_ChildUI)	// ����! ������� ���Ҹ� ����, ������� ������ �ڵ庯��; ����, ������ ���� ��, ��ȸ������ ���� �ʿ�.
		{
			if (nullptr == (T_UI))			// ����ڵ�
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
	if (ImGui::IsWindowFocused(ImGuiFocusedFlags_ChildWindows))		// ����! ImGui�� ������� ��Ŀ���� ��� WinAPI�ʹ� �޸�, ����ؼ� ��Ŀ�̿��θ� �ڵ����� ����!
	{
		if (false == M_IsFocus)				// ��Ŀ�̵� ���°� �ƴϾ��ٸ�
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
