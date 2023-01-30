#ifdef ST_PLATFORM_WINDOWS

#include "Platform/Window/Win32/Win32Input.hpp"
#include "Platform/Window/Win32/Win32InputMapper.hpp"
#include "Satoshi/Core/Application.hpp"
#include <windows.h>

bool Satoshi::Win32Input::IsKeyPressedImpl(uint32_t keycode)
{
    uint16_t keyState = GetKeyState(Win32InputMapper::MapInput(keycode));
    return keyState & BIT(15);
}

bool Satoshi::Win32Input::IsMouseButtonPressedImpl(uint32_t button)
{
    uint16_t buttonState = GetKeyState(Win32InputMapper::MapInput(button));
    return buttonState & BIT(15);
}

float Satoshi::Win32Input::GetMouseXImpl()
{
    return GetMousePosImpl().first;
}

float Satoshi::Win32Input::GetMouseYImpl()
{
    return GetMousePosImpl().second;
}

std::pair<float, float> Satoshi::Win32Input::GetMousePosImpl()
{
    HWND window = std::any_cast<HWND>(Satoshi::Application::GetInstance()->GetWindow()->GetNativeWindow());
    RECT windowPos;
    POINT mousePos;
    GetWindowRect(window, &windowPos);
    GetCursorPos(&mousePos);
    return std::pair<float, float>((float)(mousePos.x - windowPos.left), (float)(mousePos.y - windowPos.top));
}

#endif
