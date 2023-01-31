#include "Satoshi/ImGUI/WindowImGUILayer.hpp"
#ifdef ST_PLATFORM_WINDOWS
#include "Platform/Window/Win32/Win32ImGUILayer.hpp"
#endif

Satoshi::WindowImGUILayer* Satoshi::WindowImGUILayer::Create()
{
#ifdef ST_PLATFORM_WINDOWS
    return new Win32ImGUILayer();
#endif
}
