#ifdef ST_PLATFORM_WINDOWS

#ifndef WIN32_WINDOW_HPP
#define WIN32_WINDOW_HPP

#include "Satoshi/Window.hpp"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <tchar.h>
#include <stdbool.h>

#include <glad/wgl.h>
#include <glad/wglext.h>

namespace Satoshi
{
    struct WindowData
    {
        std::wstring Title;
        bool VSync;
        uint32_t Width, Height;
        EventCallbackFn EventCallback;
    };
    class Win32Window : public Window
    {
    public:
        Win32Window(const WindowProps& props);
        ~Win32Window();

        virtual void OnUpdate() override;

        virtual uint32_t GetWidth() const override;
        virtual uint32_t GetHeight() const override;

        virtual bool ShouldClose() const override;
        virtual void SetCloseState(bool value) override;

        virtual void SetEventCallback(const EventCallbackFn& callback) override;
        //This responsability should be passed to the device context(in openGL isn't obvious the reason, it become visible in D3D11)
        virtual void SetVSync(bool enabled) override;
        virtual bool IsVSync() const override;
    private:

        void CreateWindowClass(HINSTANCE* instance);
        static void AdjustDimensions(LPRECT originalDimensions, DWORD flags);
        void InitOpenGL();

#pragma region OGL
        HDC m_HDC;
        HGLRC m_HRC;
        PFNWGLSWAPINTERVALEXTPROC SwapIntervalEXT;
#pragma endregion

        HWND m_WindowHandle;
        WNDCLASSEXW m_WindowClass = { 0 };
        MSG m_MSG = { 0 };

        WindowData m_WindowData;
        bool m_ShouldClose;

        
    };
}


#endif //WIN32_WINDOW_HPP

#endif // ST_PLATFORM_WINDOWS
