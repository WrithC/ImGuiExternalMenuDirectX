#pragma once

#include <d3d9.h>
#include <string>

namespace gui
{
	inline bool running = true;
	
	// DirectX9 state vars
	inline LPDIRECT3D9 pD3D = nullptr;
	inline LPDIRECT3DDEVICE9 pD3DDevice = nullptr;
	inline D3DPRESENT_PARAMETERS presentParameters = {};

	// WinAPI const and vars
	inline HWND hWindow = nullptr;
	inline WNDCLASSEXA windowClass = {};
	inline POINTS cursorPosition = {}; // Relative to the screen
	constexpr int WIDTH = 2000;
	constexpr int HEIGHT = 2000;

	bool CreateWinAPIWindow(const char* windowName, const char* windowClassName) noexcept;
	void DestroyWinAPIWindow() noexcept;

	bool CreateD3DDevice() noexcept;
	void ResetD3DDevice() noexcept;
	void DestroyD3DDevice() noexcept;

	bool CreateImGuiContext() noexcept;
	void DestroyImGuiContext() noexcept;

	void NewFrame() noexcept;
	void RenderFrame() noexcept;
	void EndFrame() noexcept;
}

LRESULT WINAPI WndProc(
	HWND hWnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam);