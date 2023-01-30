#include "Satoshi/Window.hpp"
#include "Platform/Window/Win32/Win32Window.hpp"

Satoshi::Window* Satoshi::Window::Create(const WindowProps& props)
{
#ifdef ST_PLATFORM_WINDOWS
    return new Win32Window(props);
#endif
}
