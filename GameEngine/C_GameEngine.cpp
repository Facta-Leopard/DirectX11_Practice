#include "pch.h"
#include "framework.h"

#include "C_GameEngine.h"


int C_GameEngine::MF_Innitialize()
{

	// 관리자 생성

    // 창 생성
    MF_CreateWindow();

    return S_OK;
}

void C_GameEngine::MF_Prograss()
{
}

int C_GameEngine::MF_CreateWindow()
{
    MH_Window = CreateWindowW(L"MyWindow", L"DirectX53", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, MH_Instance, nullptr);


    if (!MH_Window)
    {
        POPUP(L"창 생성 실패", L"C_GameEngine.cpp 확인");
        return E_FAIL;
    }

    ShowWindow(MH_Window, true);
    UpdateWindow(MH_Window);

    // 입력된 해상도에 맞는 윈도우 크기 설정
    RECT windowSize = { 0, 0, (int)MV2_Resolution.x, (int)MV2_Resolution.y };
    AdjustWindowRect(&windowSize, WS_OVERLAPPEDWINDOW, !!GetMenu(MH_Window));
    SetWindowPos(MH_Window, nullptr, 0, 0, windowSize.right - windowSize.left, windowSize.bottom - windowSize.top, 0);

    return S_OK;
}