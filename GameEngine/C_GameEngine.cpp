#include "pch.h"

#include "C_GameEngine.h"

C_GameEngine::C_GameEngine()
{
}

C_GameEngine::~C_GameEngine()
{
}

void C_GameEngine::MF_Initialize()
{

	// 관리자 생성

    // 창 생성
    MF_CreateWindow();
 
    // 객체 구별용 ID값 초기화
    M_IDCount = 0;
}

void C_GameEngine::MF_Prograss()
{
}

void C_GameEngine::MF_CreateWindow()
{
    M_H_WindowHandle = CreateWindowW(L"MyWindow", L"DirectX53", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, M_H_Instance, nullptr);


    if (!M_H_WindowHandle)
    {
        POPUP(L"Window Creating Failed", L"CreateWindowW 실패");
        return;
    }

    ShowWindow(M_H_WindowHandle, true);
    UpdateWindow(M_H_WindowHandle);

    // 입력된 해상도에 맞는 윈도우 크기 설정
    RECT windowSize = { 0, 0, (int)M_V2_Resolution.x, (int)M_V2_Resolution.y };
    AdjustWindowRect(&windowSize, WS_OVERLAPPEDWINDOW, !!GetMenu(M_H_WindowHandle));
    SetWindowPos(M_H_WindowHandle, nullptr, 0, 0, windowSize.right - windowSize.left, windowSize.bottom - windowSize.top, 0);
}