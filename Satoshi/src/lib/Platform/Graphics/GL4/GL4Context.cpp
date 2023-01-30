#include "Platform/Graphics/GL4/GL4Context.hpp"
#include <cassert>
#include "Satoshi/Core/Application.hpp"

Satoshi::GL4Context::GL4Context()
{
    m_ClearColor[0] = 1.0f;
    m_ClearColor[1] = .0f;
    m_ClearColor[2] = .3f;
    m_ClearColor[3] = 1.0f;

    m_HDC = GetDC(std::any_cast<HWND>(Application::GetInstance()->GetWindow()->GetNativeWindow()));
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
    m_HRC = NULL;
    assert(nullptr != (m_HRC = wglCreateContextAttribsARB(m_HDC, NULL, attributes)));
    wglMakeCurrent(NULL, NULL); // Remove the temporary context from being active
    wglDeleteContext(temp_context); // Delete the temporary OpenGL context
    wglMakeCurrent(m_HDC, m_HRC);    // Make our OpenGL 3.2 context current

    SwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
    // Glad Loader!
    assert(gladLoaderLoadGL());
    m_GLSLImGUIVersion = "#version 410";
}

Satoshi::GL4Context::~GL4Context()
{
    wglDeleteContext(m_HRC);
    ReleaseDC(std::any_cast<HWND>(Application::GetInstance()->GetWindow()->GetNativeWindow()), m_HDC);
}

void Satoshi::GL4Context::Present()
{
    if (SwapIntervalEXT)
        SwapIntervalEXT(1);
    SwapBuffers(m_HDC);
}

void Satoshi::GL4Context::Update()
{
    glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Satoshi::GL4Context::SetClearColor(float r, float g, float b, float a)
{
    m_ClearColor[0] = r;
    m_ClearColor[1] = g;
    m_ClearColor[2] = b;
    m_ClearColor[3] = a;
}

std::any Satoshi::GL4Context::GetImGUIData()
{
    return m_GLSLImGUIVersion;
}
