#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_dx9.h"
#include "../imgui/imgui_impl_win32.h"
#include "gui.h"

bool gui::CreateWinAPIWindow(
    const char* windowName,
    const char* windowClassName
) noexcept
{
    // Populate window parameters
    windowClass.cbSize = sizeof(WNDCLASSEXA);
    windowClass.lpfnWndProc = WndProc;
    windowClass.hInstance = GetModuleHandle(nullptr);
    windowClass.lpszClassName = windowClassName;
    windowClass.cbWndExtra = 0;
    windowClass.cbClsExtra = 0;
    windowClass.hCursor = nullptr;
    windowClass.hIcon = nullptr;
    windowClass.hIconSm  = nullptr;
    windowClass.hbrBackground = nullptr;
    windowClass.lpszMenuName = nullptr;

    RegisterClassExA(&windowClass);

    hWindow = CreateWindowExA(
        WS_EX_LEFT,
        windowClassName,
        windowName,
        WS_POPUP,
        300, 300,
        WIDTH, HEIGHT,
        NULL,
        NULL,
        windowClass.hInstance,
        nullptr
    );

    if (hWindow == nullptr)
    {
        return false;
    }

    ShowWindow(hWindow, SW_SHOWDEFAULT);
    UpdateWindow(hWindow);

    return true;
}

void gui::DestroyWinAPIWindow() noexcept
{
    DestroyWindow(hWindow);
    UnregisterClass(
        windowClass.lpszClassName,
        windowClass.hInstance
    );
}

bool gui::CreateD3DDevice() noexcept
{
    
}

void gui::ResetD3DDevice() noexcept
{

}

void gui::DestroyD3DDevice() noexcept
{

}

bool gui::CreateImGuiContext() noexcept
{

}

void gui::DestroyImGuiContext() noexcept
{

}

void gui::BeginRender() noexcept
{

}

void gui::Render() noexcept
{

}

void gui::EndRender() noexcept
{

}

// Message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Our message handler passes what it can to ImGui but handles remaining cases
LRESULT WINAPI WndProc(
	HWND hWnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam
)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;

    switch (msg)
    {
    case WM_SIZE:
        if (gui::pD3DDevice != nullptr && wParam != SIZE_MINIMIZED)
        {
            gui::presentParameters.BackBufferWidth = LOWORD(lParam);
            gui::presentParameters.BackBufferHeight = HIWORD(lParam);
            gui::ResetD3DDevice();
        }
        return 0;
    
    // Disable ALT application menu
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU)
        {
            return 0;
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    // Set cursor position
    case WM_LBUTTONDOWN:
        gui::cursorPosition = MAKEPOINTS(lParam);
        return 0;

    // Logic to handle moving the window
    case WM_MOUSEMOVE:
        if (wParam != MK_LBUTTON)
        {
            return 0;
        }

        //Validate that the window won't have bad position after moving
        if (!(gui::cursorPosition.x >= 0 && gui::cursorPosition.y >= 0))
        {
            return 0;
        }
        
        const POINTS newCursorPosition = MAKEPOINTS(lParam);
        
        // Create rectangle with same corners as out window
        RECT windowRectangle = {};
        GetWindowRect(gui::hWindow, &windowRectangle);

        // Resize the window rectangle based of difference in x / y pos
        windowRectangle.left += (newCursorPosition.x - gui::cursorPosition.x);
        windowRectangle.top += (newCursorPosition.y - gui::cursorPosition.y);

        SetWindowPos(
            gui::hWindow,
            HWND_TOPMOST, // Displays infront of everything else
            windowRectangle.left,
            windowRectangle.top,
            0, 0, // Resizing params are ignored due to later flags
            SWP_NOZORDER | SWP_NOSIZE | SWP_SHOWWINDOW // Don't change z pos, don't resize and don't hide the window
        );

        return 0;
    }

    return DefWindowProcW(hWnd, msg, wParam, lParam);
}
