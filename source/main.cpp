#include "gui.h"
#include <thread>

int __stdcall wWinMain(
	HINSTANCE hInstance, 
	HINSTANCE hPrevInstance,
	PWSTR lpCmdLine,
	int nShowCmd
)
{
	gui::CreateWinAPIWindow("Menu", "Menu class");
	gui::CreateD3DDevice();
	gui::CreateImGuiContext();

	while (gui::running)
	{
		gui::NewFrame();
		gui::RenderFrame();
		gui::EndFrame();
		std::this_thread::sleep_for(std::chrono::milliseconds(15));
	}

	gui::DestroyWinAPIWindow();
	gui::DestroyD3DDevice();
	gui::DestroyWinAPIWindow();

	return EXIT_SUCCESS;
}