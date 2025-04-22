#pragma once

#include "pch.h"
#include "../GameEngine/C_Singleton.h"

#include <unordered_map>

#include <string>
#include <d3d11.h>

using namespace std;

class C_UI;

class C_UIManager :
	public C_Singleton<C_UIManager>
{
	SINGLE(C_UIManager)

protected:
	unordered_map<string, C_UI*>				STL_I_M_UI;				// unordered_map<string, C_UI*>;

public:
	void MF_Initialize(HWND _WindowHandle, ComPtr<ID3D11Device> _Device, ComPtr<ID3D11DeviceContext> _DeviceContext);

	void MF_Update();

public:
	inline C_UI* MF_Get_UI(const string& _Name)
	{
		unordered_map<string, C_UI*>::iterator T_Iterator = STL_I_M_UI.find(_Name);

		if (nullptr == T_Iterator->second)		// 방어코드
		{
			return nullptr;
		}
		return T_Iterator->second;
	}
};

