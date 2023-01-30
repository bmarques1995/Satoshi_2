#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Core.hpp"
#include "Window.hpp"
#include <stpch.hpp>

namespace Satoshi
{
    class SATOSHI_API Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();
    private:
        std::unique_ptr<Window> m_Window;
    };

    Application* CreateApplication();
}


#endif // APPLICATION_HPP
