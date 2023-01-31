#include "Satoshi/Window/Input.hpp"

#ifdef ST_PLATFORM_WINDOWS

#include "Platform/Window/Win32/Win32Input.hpp"

Satoshi::Input* Satoshi::Input::s_Instance = new Win32Input();

#endif
