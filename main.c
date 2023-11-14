#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#define Assert(c) do { if (!(c)) __debugbreak(); } while (0)

#pragma comment (lib, "user32.lib")

LRESULT CALLBACK WindowProc(HWND window, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch(msg) {
        case WM_DESTROY: {
            PostQuitMessage(0);
        } break;
        case WM_KEYDOWN: {
            switch(wParam) {
                case 'O': {
                    DestroyWindow(window);
                } break;
            }
        } break;
        default: {
            return DefWindowProcW(window, msg, wParam, lParam);
        }
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE pInstance, LPSTR cmd, int cmdShow) {
    WNDCLASSW wc = {
        .lpszClassName = L"MyWindowClass",
        .lpfnWndProc = WindowProc,
        .hInstance = instance,
        .hCursor = LoadCursor(NULL, IDC_CROSS),
    };
    ATOM atom = RegisterClassW(&wc);
    Assert(atom && "Failed to register a window");
    
    HWND window = CreateWindowW(wc.lpszClassName, L"Window Creation", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, instance, NULL);
    Assert(window && "Failed to create a window");
    
    ShowWindow(window, cmdShow);
    
    for(;;) {
        MSG msg;
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if(msg.message == WM_QUIT) break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            continue;
        }    
    }
    return 0;
}
