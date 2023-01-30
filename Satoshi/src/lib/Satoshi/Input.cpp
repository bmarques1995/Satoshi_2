#include "Satoshi/Input.hpp"
#include "Platform/Window/Win32/Win32Input.hpp"

#ifdef ST_PLATFORM_WINDOWS

Satoshi::Input* Satoshi::Input::s_Instance = new Win32Input();

#endif
