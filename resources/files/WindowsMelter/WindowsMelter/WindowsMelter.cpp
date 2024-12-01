#pragma warning(disable : 28251)

// This code is protected by copyright laws, including the DMCA (Digital Millennium Copyright Act).
// Any reproduction, modification, or distribution without explicit authorization is prohibited and may result in legal action.
// © Maybe Ange™ Corporation. All rights reserved.

#include <windows.h>
#include <vector>

struct MonitorInfo {
    RECT rect;
};

std::vector<MonitorInfo> monitors;

int nRandWidth = 150, nRandHeight = 15, nSpeed = 1;

LRESULT WINAPI MelterProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    switch (Msg) {
    case WM_CREATE:
    {
        HDC hdcDesktop = GetDC(HWND_DESKTOP);
        HDC hdcWindow = GetDC(hWnd);

        RECT rect;
        GetWindowRect(hWnd, &rect);
        int nScreenWidth = rect.right - rect.left;
        int nScreenHeight = rect.bottom - rect.top;

        BitBlt(hdcWindow, 0, 0, nScreenWidth, nScreenHeight, hdcDesktop, rect.left, rect.top, SRCCOPY);

        ReleaseDC(hWnd, hdcWindow);
        ReleaseDC(HWND_DESKTOP, hdcDesktop);

        SetWindowLongPtr(hWnd, GWL_EXSTYLE, GetWindowLongPtr(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED | WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE);
        SetLayeredWindowAttributes(hWnd, RGB(0, 0, 0), 0, LWA_COLORKEY);

        SetWindowLongPtr(hWnd, GWL_EXSTYLE, GetWindowLongPtr(hWnd, GWL_EXSTYLE) | WS_EX_TRANSPARENT);

        SetTimer(hWnd, 0, nSpeed, NULL);
        ShowWindow(hWnd, SW_SHOW);
    }
    return 0;

    case WM_ERASEBKGND:
        return 0;
    case WM_PAINT:
        ValidateRect(hWnd, NULL);
        return 0;
    case WM_TIMER:
    {
        HDC hdcWindow = GetDC(hWnd);

        RECT rect;
        GetWindowRect(hWnd, &rect);
        int nScreenWidth = rect.right - rect.left;
        int nScreenHeight = rect.bottom - rect.top;

        int nXPos = (rand() % nScreenWidth) - (nRandWidth / 2),
            nYPos = (rand() % nRandHeight),
            nWidth = (rand() % nRandWidth);
        BitBlt(hdcWindow, nXPos, nYPos, nWidth, nScreenHeight, hdcWindow, nXPos, 0, SRCCOPY);
        ReleaseDC(hWnd, hdcWindow);
    }
    return 0;

    case WM_CLOSE:
    case WM_DESTROY:
    {
        KillTimer(hWnd, 0);
        PostQuitMessage(0);
    }
    return 0;

    case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN:
    case WM_MBUTTONDOWN:
    case WM_MOUSEMOVE:
    case WM_NCLBUTTONDOWN:
    case WM_NCRBUTTONDOWN:
        return 0;

    }
    return DefWindowProc(hWnd, Msg, wParam, lParam);
}

BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)
{
    MonitorInfo info = { *lprcMonitor };
    monitors.push_back(info);
    return TRUE;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    HWND hWndMsgBox = FindWindow(NULL, L"L'elite de la nation");
    if (hWndMsgBox) {
        SetWindowPos(hWndMsgBox, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    }
    EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, 0);

    WNDCLASS wndClass = { 0, MelterProc, 0, 0, hInstance, NULL, LoadCursor(NULL, IDC_ARROW), 0, NULL, L"Melter" };
    if (!RegisterClass(&wndClass)) return MessageBox(HWND_DESKTOP, L"Cannot register class!", NULL, MB_ICONERROR | MB_OK);

    std::vector<HWND> windows;
    for (const auto& monitor : monitors) {
        HWND hWnd = CreateWindow(L"Melter", NULL, WS_POPUP | WS_VISIBLE | WS_EX_TOPMOST | WS_EX_TOOLWINDOW,
            monitor.rect.left, monitor.rect.top,
            monitor.rect.right - monitor.rect.left,
            monitor.rect.bottom - monitor.rect.top,
            HWND_DESKTOP, NULL, hInstance, NULL);

        if (!hWnd) return MessageBox(HWND_DESKTOP, L"Cannot create window!", NULL, MB_ICONERROR | MB_OK);

        SetWindowPos(hWnd, HWND_TOPMOST, monitor.rect.left, monitor.rect.top, 0, 0, SWP_NOACTIVATE | SWP_NOSIZE);
        SetWindowPos(hWnd, HWND_TOPMOST, monitor.rect.left, monitor.rect.top, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);

        windows.push_back(hWnd);
    }

    srand(GetTickCount64());
    MSG Msg = { 0 };
    while (Msg.message != WM_QUIT) {
        if (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&Msg);
            DispatchMessage(&Msg);
        }
        if (GetAsyncKeyState(VK_HOME) & 0x8000) {
            for (auto hWnd : windows) {
                DestroyWindow(hWnd);
            }
        }
    }
    return 0;
}