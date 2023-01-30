#include "Satoshi/Application.hpp"
#include "Satoshi/Console.hpp"
#include "Satoshi/Events/ApplicationEvent.hpp"

Satoshi::Application::Application()
{
	Console::Init();
	m_Window.reset(Window::Create());
	m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
}

Satoshi::Application::~Application()
{
	m_Window.reset();
	Console::End();
}

void Satoshi::Application::Run()
{
	Console::CoreWarn("Initialized Log");
	Console::CoreLog("Hello, this Engine will first support {0}, but soon I will add {1}, {2} and {3}","GL4","D3D11","VK","D3D12");
	WindowResizeEvent e(1280, 720);
	Console::Log(e.ToString());
	while (!m_Window->ShouldClose())
	{
		m_Window->OnUpdate();
	}
}

void Satoshi::Application::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
	Console::Log(e.ToString());
}

bool Satoshi::Application::OnWindowClose(WindowCloseEvent& e)
{
	m_Window->SetCloseState(true);
	return true;
}
