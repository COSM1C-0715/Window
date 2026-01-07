#include "Window.h"
#include "Input.h"
#include<Windows.h>
#include<d3d12.h>
#include <dxgi1_4.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT umsg, WPARAM wParam, LPARAM lParam)
{
    switch (umsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, umsg, wParam, lParam);
}

HRESULT Window::createWindow(HINSTANCE hInstance, int Width_, int Height_, std::string_view name)
{
    WNDCLASS wc{};// ここにメインの処理を書く

    // 1. ウィンドウクラス登録
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = name.data();
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    RegisterClass(&wc);
    // 2. ウィンドウ作成
    hwnd = CreateWindow(
        wc.lpszClassName,
        wc.lpszClassName,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        Width_,Height_,
        NULL, NULL,
        hInstance,
        NULL);

    ShowWindow(hwnd, SW_SHOW);

    UpdateWindow(hwnd);

    width = Width_;
    height = Height_;

    return S_OK;
}

bool Window::MassageLoop()
{
    bool nextFrame = true;
    MSG msg{};
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                nextFrame = false;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            static byte keyState[256]{};
            if (GetKeyboardState(keyState))
            {
                Input::instance().updateKeyState(keyState);
            }
        }

    return true;
}

HWND Window::Handle()
{
    return hwnd;
}

std::pair<int, int> Window::size()
{
    return {width,height};
}
