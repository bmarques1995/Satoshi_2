#ifdef ST_PLATFORM_WINDOWS

#ifndef WIN32_WINDOW_HPP
#define WIN32_WINDOW_HPP

#include "Satoshi/Window.hpp"
#include <windows.h>

namespace Satoshi
{
    class Win32Window : public Window
    {
    public:
        Win32Window(const WindowProps& props);
        ~Win32Window();

        virtual void OnUpdate() override;

        virtual uint32_t GetWidth() const override;
        virtual uint32_t GetHeight() const override;

        virtual bool ShouldClose() const override;

        virtual void SetEventCallback(const EventCallbackFn& callback) override;
        //This responsability should be passed to the device context(in openGL isn't obvious the reason, it become visible in D3D11)
        virtual void SetVSync(bool enabled) override;
        virtual bool IsVSync() const override;
    private:

        void CreateWindowClass(HINSTANCE* instance);
        static void AdjustDimensions(LPRECT originalDimensions, DWORD flags);

        HWND m_WindowHandle;
        WNDCLASSEXW m_WindowClass = { 0 };
        MSG m_MSG = { 0 };

        std::wstring m_Title;
        bool m_VSync;
        uint32_t m_Width, m_Height;
        bool m_ShouldClose;

        EventCallbackFn m_EventCallback;
    };
}


#endif //WIN32_WINDOW_HPP

#endif // ST_PLATFORM_WINDOWS
