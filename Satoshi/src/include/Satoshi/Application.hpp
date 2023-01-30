#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Core.hpp"

namespace Satoshi
{
    class SATOSHI_API Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();
    private:

    };

    Application* CreateApplication();
}


#endif // APPLICATION_HPP
