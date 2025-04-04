#include "pch.h"

#include "C_GameEngine.h"


HRESULT C_GameEngine::MF_Innitialize()
{

	// 관리자 생성

    // 창 생성
    if (FAILED(MF_CreateWindow()))
    {
        POPUP(L"Window Creating Failed", L"C_GameEngine::MFCreateWindow 실패");
        return E_FAIL;
    }
 
    // 객체 구별용 ID값 초기화
    M_IDCount = 0;
    
    return S_OK;
}

void C_GameEngine::MF_Prograss()
{
}

HRESULT C_GameEngine::MF_CreateWindow()
{
    M_H_Window = CreateWindowW(L"MyWindow", L"DirectX53", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, M_H_Instance, nullptr);


    if (!M_H_Window)
    {
        POPUP(L"창 생성 실패", L"C_GameEngine.cpp 확인");
        return E_FAIL;
    }

    ShowWindow(M_H_Window, true);
    UpdateWindow(M_H_Window);

    // 입력된 해상도에 맞는 윈도우 크기 설정
    RECT windowSize = { 0, 0, (int)M_V2_Resolution.x, (int)M_V2_Resolution.y };
    AdjustWindowRect(&windowSize, WS_OVERLAPPEDWINDOW, !!GetMenu(M_H_Window));
    SetWindowPos(M_H_Window, nullptr, 0, 0, windowSize.right - windowSize.left, windowSize.bottom - windowSize.top, 0);

    return S_OK;
}