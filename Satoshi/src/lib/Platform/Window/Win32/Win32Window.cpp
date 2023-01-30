#ifdef ST_PLATFORM_WINDOWS

#include "Platform/Window/Win32/Win32Window.hpp"
#include "Satoshi/Events/ApplicationEvent.hpp"
#include "Satoshi/Events/KeyEvent.hpp"
#include "Satoshi/Events/MouseEvent.hpp"
#include "imgui.h"
#include "backends/imgui_impl_win32.h"

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

    InitOpenGL();
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
    glClearColor(1.0f,.0f,.3f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
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

std::any Satoshi::Win32Window::GetNativeWindow() const
{
    return m_WindowHandle;
}

void Satoshi::Win32Window::Present() const
{
    if(SwapIntervalEXT)
        SwapIntervalEXT(1);
    SwapBuffers(m_HDC);
}

void Satoshi::Win32Window::SetVSync(bool enabled)
{
    m_WindowData.VSync = enabled;
}

bool Satoshi::Win32Window::IsVSync() const
{
	return m_WindowData.VSync;
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

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

        if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
            return true;
        if (msg == WM_NCCREATE)
            return DefWindowProcW(hWnd, msg, wParam, lParam);

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

void Satoshi::Win32Window::InitOpenGL()
{
    m_HDC = GetDC(m_WindowHandle);
    assert(m_HDC != nullptr);
    // Set the pixel format for the device context:
    PIXELFORMATDESCRIPTOR pfd = { };
    pfd.nSize = sizeof(pfd);
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);  // Set the size of the PFD to the size of the class
    pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;   // Enable double buffering, opengl support and drawing to a window
    pfd.iPixelType = PFD_TYPE_RGBA; // Set our application to use RGBA pixels
    pfd.cColorBits = 32;        // Give us 32 bits of color information (the higher, the more colors)
    pfd.cDepthBits = 32;        // Give us 32 bits of depth information (the higher, the more depth levels)
    pfd.iLayerType = PFD_MAIN_PLANE;    // Set the layer of the PFD
    int format = ChoosePixelFormat(m_HDC, &pfd);
    assert(format != 0 && SetPixelFormat(m_HDC, format, &pfd) != FALSE);
    // Create and enable a temporary (helper) opengl context:
    HGLRC temp_context = NULL;
    assert(nullptr != (temp_context = wglCreateContext(m_HDC)));
    wglMakeCurrent(m_HDC, temp_context);

    // Load WGL Extensions:
    gladLoaderLoadWGL(m_HDC);

    // Set the desired OpenGL version:
    int attributes[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 4,   // Set the MAJOR version of OpenGL to 3
        WGL_CONTEXT_MINOR_VERSION_ARB, 5,   // Set the MINOR version of OpenGL to 2
        WGL_CONTEXT_FLAGS_ARB,
        WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB, // Set our OpenGL context to be forward compatible
        0
    };

    auto wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
    // Create the final opengl context and get rid of the temporary one:
    HGLRC opengl_context = NULL;
    assert(nullptr != (opengl_context = wglCreateContextAttribsARB(m_HDC, NULL, attributes)));
    wglMakeCurrent(NULL, NULL); // Remove the temporary context from being active
    wglDeleteContext(temp_context); // Delete the temporary OpenGL context
    wglMakeCurrent(m_HDC, opengl_context);    // Make our OpenGL 3.2 context current

    SwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
    // Glad Loader!
    assert(gladLoaderLoadGL());
}

#endif // ST_PLATFORM_WINDOWS