#ifdef ST_PLATFORM_WINDOWS

#include "Platform/Windows/Win32Window.hpp"
#include "Satoshi/Events/ApplicationEvent.hpp"
#include "Satoshi/Events/KeyEvent.hpp"
#include "Satoshi/Events/MouseEvent.hpp"

Satoshi::Win32Window::Win32Window(const WindowProps& props)
{
    m_WindowData.Title = std::wstring(props.Title.begin(), props.Title.end());
    m_WindowData.Width = props.Width;
    m_WindowData.Height = props.Height;
    m_ShouldClose = false;
    //window
    HINSTANCE hInstance = GetModuleHandleW(NULL);
    LPWSTR cmdLine = GetCommandLineW();
    DWORD cmdShow = 10;
    RECT windowDimensions = { 0, 0, (LONG)m_WindowData.Width, (LONG)m_WindowData.Height };

    CreateWindowClass(&hInstance);
    RegisterClassExW(&m_WindowClass);

    DWORD windowedFlags = WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_SYSMENU | WS_MINIMIZEBOX | WS_CAPTION | WS_MAXIMIZEBOX | WS_THICKFRAME;

    AdjustDimensions(&windowDimensions, windowedFlags);

    m_WindowHandle = CreateWindowExW
    (
        0,
        m_WindowData.Title.c_str(),
        m_WindowData.Title.c_str(),
        windowedFlags,
        100,
        100,
        windowDimensions.right - windowDimensions.left,
        windowDimensions.bottom - windowDimensions.top,
        nullptr,
        nullptr,
        m_WindowClass.hInstance,
        nullptr
    );

    auto test = GetLastError();
    assert(GetLastError() == 0);

    SetWindowLongPtrW(m_WindowHandle, 0, (LONG_PTR)&m_WindowData);

    ShowWindow(m_WindowHandle, cmdShow);
    UpdateWindow(m_WindowHandle);
}

Satoshi::Win32Window::~Win32Window()
{
    DestroyWindow(m_WindowHandle);
    UnregisterClassW(m_WindowClass.lpszClassName, m_WindowClass.hInstance);
}

void Satoshi::Win32Window::OnUpdate()
{
    if (::PeekMessage(&m_MSG, NULL, 0, 0, PM_REMOVE))
    {
        ::TranslateMessage(&m_MSG);
        ::DispatchMessage(&m_MSG);
    }
}

uint32_t Satoshi::Win32Window::GetWidth() const
{
	return m_WindowData.Width;
}

uint32_t Satoshi::Win32Window::GetHeight() const
{
	return m_WindowData.Height;
}

bool Satoshi::Win32Window::ShouldClose() const
{
    return m_ShouldClose;
}

void Satoshi::Win32Window::SetCloseState(bool value)
{
    m_ShouldClose = value;
}

void Satoshi::Win32Window::SetEventCallback(const EventCallbackFn& callback)
{
    m_WindowData.EventCallback = callback;
}

void Satoshi::Win32Window::SetVSync(bool enabled)
{
    m_WindowData.VSync = enabled;
}

bool Satoshi::Win32Window::IsVSync() const
{
	return m_WindowData.VSync;
}

void Satoshi::Win32Window::CreateWindowClass(HINSTANCE* instance)
{
    m_WindowClass = { 0 };
    m_WindowClass.hInstance = *instance;
    m_WindowClass.cbSize = sizeof(m_WindowClass);
    m_WindowClass.cbClsExtra = 0;
    m_WindowClass.cbWndExtra = sizeof(void*);
    m_WindowClass.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
    m_WindowClass.hIcon = nullptr;
    m_WindowClass.hCursor = LoadCursor(m_WindowClass.hInstance, IDC_ARROW);
    m_WindowClass.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
    m_WindowClass.lpszClassName = m_WindowData.Title.c_str();
    m_WindowClass.lpszMenuName = nullptr;

    m_WindowClass.lpfnWndProc = [](HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT
    {
        //window resize
        //window close

        WindowData* data = (WindowData*)GetWindowLongPtr(hWnd, 0);

        switch (msg)
        {
        case WM_SIZING:
        {
            RECT clientArea;
            GetClientRect(hWnd, &clientArea);
            WindowResizeEvent e((unsigned)(clientArea.right - clientArea.left), (unsigned)(clientArea.bottom - clientArea.top));
            data->Width = e.GetWidth();
            data->Height = e.GetHeight();
            data->EventCallback(e);
            break;
        }
        case WM_CLOSE:
        case WM_QUIT:
        {
            WindowCloseEvent e;
            data->EventCallback(e);
            break;
        }
        case WM_KEYDOWN:
        {
            uint16_t repeated = (bool)(HIWORD(lParam) & KF_REPEAT);
            KeyPressedEvent event(static_cast<uint32_t>(wParam), repeated);
            data->EventCallback(event);
            break;
        }
        case WM_KEYUP:
        {
            KeyReleasedEvent event(static_cast<uint32_t>(wParam));
            data->EventCallback(event);
            break;
        }
        case WM_CHAR:
        {
            KeyTypedEvent event(static_cast<uint32_t>(wParam));
            data->EventCallback(event);
            break;
        }
        case WM_LBUTTONDOWN:
        {
            MouseButtonPressedEvent event(0);
            data->EventCallback(event);
            break;
        }
        case WM_MBUTTONDOWN:
        {
            MouseButtonPressedEvent event(2);
            data->EventCallback(event);
            break;
        }
        case WM_RBUTTONDOWN:
        {
            MouseButtonPressedEvent event(1);
            data->EventCallback(event);
            break;
        }
        case WM_XBUTTONDOWN:
        {
            MouseButtonPressedEvent event((unsigned)wParam);
            data->EventCallback(event);
            break;
        }
        case WM_LBUTTONUP:
        {
            MouseButtonReleasedEvent event(0);
            data->EventCallback(event);
            break;
        }
        case WM_MBUTTONUP:
        {
            MouseButtonReleasedEvent event(2);
            data->EventCallback(event);
            break;
        }
        case WM_RBUTTONUP:
        {
            MouseButtonReleasedEvent event(1);
            data->EventCallback(event);
            break;
        }
        case WM_XBUTTONUP:
        {
            MouseButtonReleasedEvent event((unsigned)wParam);
            data->EventCallback(event);
            break;
        }
        case WM_MOUSEHWHEEL:
        {
            short delta = GET_WHEEL_DELTA_WPARAM(wParam);
            MouseScrolledEvent event((float)(delta / 120), 0);
            data->EventCallback(event);
            break;
        }
        case WM_MOUSEWHEEL:
        {
            short delta = GET_WHEEL_DELTA_WPARAM(wParam);
            MouseScrolledEvent event(0, (float)(delta / 120));
            data->EventCallback(event);
            break;
        }
        default:
            break;
        }

        return DefWindowProcW(hWnd, msg, wParam, lParam);
    };
}

void Satoshi::Win32Window::AdjustDimensions(LPRECT originalDimensions, DWORD flags)
{
    AdjustWindowRectEx(originalDimensions, flags, 0, 0);
}

#endif // ST_PLATFORM_WINDOWS
