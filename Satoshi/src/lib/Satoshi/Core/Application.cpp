#include "Satoshi/Core/Application.hpp"
#include "Satoshi/Core/Console.hpp"
#include "Satoshi/Events/ApplicationEvent.hpp"

Satoshi::Application* Satoshi::Application::s_Instance = nullptr;

Satoshi::Application::Application()
{
	s_Instance = this;
	Console::Init();
	m_Window.reset(Window::Create());
	m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
	m_WindowLayer.reset(new Win32ImGUILayer());
	m_Context.reset(new D3D11Context());
	m_ContextLayer.reset(new D3D11ImGUILayer());
	m_ImGUILayer.OnAttach();
	m_WindowLayer->OnAttach();
	m_ContextLayer->OnAttach();
}

Satoshi::Application::~Application()
{
	m_ContextLayer->OnDetach();
	m_WindowLayer->OnDetach();
	m_ImGUILayer.OnDetach();
	m_Context.reset();
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
		m_Context->Update();

		m_ContextLayer->BeginFrame();
		m_WindowLayer->BeginFrame();
		m_ImGUILayer.BeginFrame();
		m_ImGUILayer.OnUpdate();
		
		for (Layer* layer : m_LayerStack)
		{
			layer->OnUpdate();
		}

		m_ImGUILayer.EndFrame();
		m_WindowLayer->EndFrame();
		m_ContextLayer->EndFrame();

		m_Context->Present();
	}
}

void Satoshi::Application::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
	Console::Log(e.ToString());

	for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
	{
		--it;
		(*it)->OnEvent(e);
		if (e.Handled)
			break;
	}
}

void Satoshi::Application::PushLayer(Layer* layer)
{
	m_LayerStack.PushLayer(layer);
}

void Satoshi::Application::PushOverlay(Layer* overlay)
{
	m_LayerStack.PushOverlay(overlay);
}

bool Satoshi::Application::OnWindowClose(WindowCloseEvent& e)
{
	m_Window->SetCloseState(true);
	return true;
}
