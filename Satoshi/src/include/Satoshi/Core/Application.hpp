#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Core.hpp"
#include "Satoshi/Window/Window.hpp"
#include <stpch.hpp>

#include "Satoshi/Events/ApplicationEvent.hpp"
#include "Satoshi/Events/KeyEvent.hpp"
#include "Satoshi/Events/MouseEvent.hpp"

#include "LayerStack.hpp"
#include "Satoshi/ImGUI/ImGUILayer.hpp"
#include "Platform/Window/Win32/Win32ImGUILayer.hpp"
#include "Platform/Graphics/GL4/GL4ImGUILayer.hpp"
#include "Platform/Graphics/D3D11/D3D11ImGUILayer.hpp"
#include "Platform/Graphics/GL4/GL4Context.hpp"
#include "Platform/Graphics/D3D11/D3D11Context.hpp"

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
        GraphicsContext* GetContext() { return m_Context.get(); }
        inline static Application* GetInstance() { return s_Instance; }
    
    private:    
        static Application* s_Instance;
        bool OnWindowClose(WindowCloseEvent& e);

        std::unique_ptr<Window> m_Window;
        std::unique_ptr<GraphicsContext> m_Context;
        LayerStack m_LayerStack;

        ImGUILayer m_ImGUILayer;
        std::unique_ptr<WindowImGUILayer> m_WindowLayer;
        std::unique_ptr<ContextImGUILayer> m_ContextLayer;
    };

    Application* CreateApplication();
}


#endif // APPLICATION_HPP
