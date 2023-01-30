#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Core.hpp"
#include "Window.hpp"
#include <stpch.hpp>

#include "Satoshi/Events/ApplicationEvent.hpp"
#include "Satoshi/Events/KeyEvent.hpp"
#include "Satoshi/Events/MouseEvent.hpp"

#include "LayerStack.hpp"
#include "ImGUI/ImGUILayer.hpp"
#include "Platform/Window/Win32/Win32ImGUILayer.hpp"

namespace Satoshi
{
    class SATOSHI_API Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();

        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        Window* GetWindow() { return m_Window.get(); }
        inline static Application* GetInstance() { return s_Instance; }
    
    private:    
        static Application* s_Instance;
        bool OnWindowClose(WindowCloseEvent& e);

        std::unique_ptr<Window> m_Window;
        LayerStack m_LayerStack;

        ImGUILayer m_ImGUILayer;
        Win32ImGUILayer m_WindowLayer;
    };

    Application* CreateApplication();
}


#endif // APPLICATION_HPP
