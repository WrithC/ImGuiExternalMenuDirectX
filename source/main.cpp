#include "gui.h"
#include <thread>

int __stdcall wWinMain(
	HINSTANCE hInstance, 
	HINSTANCE hPrevInstance,
	PWSTR lpCmdLine,
	int nShowCmd
)
{
	gui::CreateWinAPIWindow(L"Menu", L"Menu class");
	gui::CreateD3DDevice();
	gui::CreateImGuiContext();

	while (gui::running)
	{
		gui::NewFrame();
		gui::RenderFrame();
		gui::EndFrame();
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}

	gui::DestroyWinAPIWindow();
	gui::DestroyD3DDevice();
	gui::DestroyWinAPIWindow();

	return EXIT_SUCCESS;
}