#include "Satoshi/Application.hpp"
#include "Satoshi/Console.hpp"
#include "Satoshi/Events/ApplicationEvent.hpp"

Satoshi::Application::Application()
{
	Console::Init();
}

Satoshi::Application::~Application()
{
	Console::End();
}

void Satoshi::Application::Run()
{
	Console::CoreWarn("Initialized Log");
	Console::CoreLog("Hello, this Engine will first support {0}, but soon I will add {1}, {2} and {3}","GL4","D3D11","VK","D3D12");
	WindowResizeEvent e(1280, 720);
	Console::Log(e.ToString());
	while (true)
	{
	}
}
