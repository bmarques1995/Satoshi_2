#ifndef ENTRYPOINT_HPP
#define ENTRYPOINT_HPP

#include "Application.hpp"

#ifdef ST_PLATFORM_WINDOWS

extern Satoshi::Application* Satoshi::CreateApplication();

int main(int argc, char** argv)
{

	Satoshi::Application* app = Satoshi::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif

#endif //ENTRYPOINT_HPP
