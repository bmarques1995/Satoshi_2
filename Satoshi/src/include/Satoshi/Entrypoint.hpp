#ifndef ENTRYPOINT_HPP
#define ENTRYPOINT_HPP

#include "Application.hpp"

#ifdef ST_PLATFORM_WINDOWS

#include <windows.h>

extern Satoshi::Application* Satoshi::CreateApplication();

INT APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nCmdShow)
{

	Satoshi::Application* app = Satoshi::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif

#endif //ENTRYPOINT_HPP
