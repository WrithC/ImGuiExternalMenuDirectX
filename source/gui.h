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
	constexpr int WIDTH = 500;
	constexpr int HEIGHT = 500;

	bool CreateWinAPIWindow(const char* windowName, const char* windowClassName) noexcept;
	void DestroyWinAPIWindow() noexcept;

	bool CreateD3DDevice() noexcept;
	void ResetD3DDevice() noexcept;
	void DestroyD3DDevice() noexcept;

	bool CreateImGuiContext() noexcept;
	void DestroyImGuiContext() noexcept;

	void BeginRender() noexcept;
	void Render() noexcept;
	void EndRender() noexcept;
}