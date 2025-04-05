#include "pch.h"

C_GameEngine::C_GameEngine()
    : M_H_Instance(nullptr)
    , M_H_WindowHandle(nullptr)
    , M_V2_Resolution(0.f, 0.f)
    , M_IDCount(0)
{
}

C_GameEngine::~C_GameEngine()
{
}

void C_GameEngine::MF_Initialize(HINSTANCE _HInstance, UINT _ResolutionX, UINT _ResoulutionY)
{
    // 메인 프로그램 인자 전달
    M_H_Instance = _HInstance;
    M_V2_Resolution.x = (float)_ResolutionX;
    M_V2_Resolution.y = (float)_ResoulutionY;

    // 창 생성
    MF_CreateWindow();

	// 관리자 생성 및 초기화
    // 향후, 추가 구현 예정
    C_InputManager::SF_GetInstance()->MF_Initialize();
    C_PathManager::SF_GetInstance()->MF_Initialize();
    C_TimeManager::SF_GetInstance()->MF_Initialize();

    // C_RenderManager::SF_GetInstance()->MF_Initialize();

#ifdef DEBUG
    C_DebugManager::SF_GetInstance()->MF_Initialize();
#endif // DEBUG
 
    // 객체 구별용 ID값 초기화
    M_IDCount = 0;
}

void C_GameEngine::MF_Prograss()
{
    // 관리자 Update
    // 향후, 추가 구현 예정
    // TaskManager::SF_GetInstance()->MF_Update();
    C_InputManager::SF_GetInstance()->MF_Update();

    C_TimeManager::SF_GetInstance()->MF_Update();

    C_RenderManager::SF_GetInstance()->MF_Update();

    
#ifdef _DEBUG
    C_DebugManager::SF_GetInstance()->MF_Update();
#endif // DEBUG


}

void C_GameEngine::MF_CreateWindow()
{
    M_H_WindowHandle = CreateWindowW(L"DirectX_Practice", L"ResidentEvil_Survivor", WS_OVERLAPPEDWINDOW, 
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, M_H_Instance, nullptr); // 유의! wcex.lpszClassName로 연결하는 기본창 클래스 이름과 일치하지 않으면 에러남


    if (!M_H_WindowHandle)
    {
        POPUP_DEBUG(L"Window Creating Failed", L"CreateWindowW 실패");
        return;
    }

    ShowWindow(M_H_WindowHandle, true);             // 창 띄우기
    UpdateWindow(M_H_WindowHandle);                 // 창 주소 연결

    // 입력된 해상도에 맞는 윈도우 크기 설정
    RECT T_WindowSize = { 0, 0, (int)M_V2_Resolution.x, (int)M_V2_Resolution.y };                                                       // 창 크기 설정; 해상도 값을 전달받아 설정
    AdjustWindowRect(&T_WindowSize, WS_OVERLAPPEDWINDOW, !!GetMenu(M_H_WindowHandle));                                                  // 창 크기 조정
    SetWindowPos(M_H_WindowHandle, nullptr, 0, 0, T_WindowSize.right - T_WindowSize.left, T_WindowSize.bottom - T_WindowSize.top, 0);   // 창 위치 지정
}