#include "Satoshi/Core/Application.hpp"
#include "Satoshi/Core/Console.hpp"
#include "Satoshi/Events/ApplicationEvent.hpp"
#include "Satoshi/Core/ApplicationStarter.hpp"
#include "Platform/Graphics/VK/VKContext.hpp"

Satoshi::Application* Satoshi::Application::s_Instance = nullptr;

Satoshi::Application::Application()
{
	s_Instance = this;
	ApplicationStarter::BuildStarter();
	json startupJson = ApplicationStarter::GetStartupJson();
	auto test = startupJson["GraphicsAPI"].get<std::string>();
	m_API = RendererAPI::MatchAPIByName(test);
	Console::Init();
	m_ImGUILayer.reset(new ImGUILayer());
	m_Window.reset(Window::Create());
	m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
	m_WindowLayer.reset(WindowImGUILayer::Create());
	m_Context.reset(GraphicsContext::Create(m_API));
	m_ContextLayer.reset(ContextImGUILayer::Create(m_API));
	m_ImGUILayer->OnAttach();
	m_WindowLayer->OnAttach();
	m_ContextLayer->OnAttach();
}

Satoshi::Application::~Application()
{
	m_ContextLayer->OnDetach();
	m_WindowLayer->OnDetach();
	m_ImGUILayer->OnDetach();
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
		m_Context->NewFrame();
		m_Context->ReceiveCommands();
		m_Context->ClearTarget();

		m_ContextLayer->BeginFrame();
		m_WindowLayer->BeginFrame();
		m_ImGUILayer->BeginFrame();
		m_ImGUILayer->OnUpdate();
		
		for (Layer* layer : m_LayerStack)
		{
			layer->OnUpdate();
		}

		m_ImGUILayer->EndFrame();
		m_WindowLayer->EndFrame();
		m_ContextLayer->EndFrame();

		m_Context->DispatchCommands();
		m_Context->Present();
		m_Context->EndFrame();
	}
}

void Satoshi::Application::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
	dispatcher.Dispatch<WindowResizeEvent>(std::bind(&Application::OnWindowResize, this, std::placeholders::_1));
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

bool Satoshi::Application::OnWindowResize(WindowResizeEvent& e)
{
	m_Context->OnResize(e);
	return false;
}
