// ResidentEvil_Survivor.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include "Resource.h"
#include "imgui/imgui.h"

#include "library\GameEngine\C_GameEngine.h"
#include "library\GameEngine\C_Device.h"

// 전역 변수:
HINSTANCE GH_Instance = nullptr;     

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    GH_Instance = hInstance;

    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_RESIDENTEVILSURVIVOR));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_RESIDENTEVILSURVIVOR);
    wcex.lpszClassName = L"ResidentEvil_Survivor";              // 기본 창 클래스 이름
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    RegisterClassExW(&wcex);


    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // 엔진 초기화
    C_GameEngine::SF_GetInstance()->MF_Innitialize();

    // 에디터 카메라 관리자 초기화


    // IMGUI 관리자 초기화



    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_RESIDENTEVILSURVIVOR));

    MSG msg;

    while (true)
    {
        // 기본 메시지 루프입니다:
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            // 윈도우 큐 시스템에 종료 메시지가 들어간 경우에는 루프에서 나옮
            if (msg.message == WM_QUIT)
                break;

            // 윈도우 메시지 콜백 프로시저 호출부분
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            // 게임엔진 루프 호출


            // 에디터 카메라 루프 호출


            // IMGUI 관련 루프 호출


            // 다이렉트로 생성된 스왑체인 화면 송출

        }
    }

    return (int) msg.wParam;
}


// IMGUI 사용을 위하여 프로시저 함수 전역 정의
// 
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// 향후, 풀스크린 및 창모드 변경 메시지 관련 - Device-쪽 윈도우 변경
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // IMGUI 적용을 위해 바로 전 콜백함수 ImGui_ImplWin32_WndProcHandler를 윈도우 프로시저에 붙혀서 사용
    if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
        return true;

    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(GH_Instance, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case IDM_FULLSCREEN:
                break;
            case IDM_WINDOWEDSCREEN:
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
