#include "Platform/Graphics/D3D11/D3D11Context.hpp"
#include <cassert>
#include "Satoshi/Core/Application.hpp"

Satoshi::D3D11Context::D3D11Context()
{
    m_ClearColor[0] = 1.0f;
    m_ClearColor[1] = .0f;
    m_ClearColor[2] = .3f;
    m_ClearColor[3] = 1.0f;

    D3D_FEATURE_LEVEL fl = D3D_FEATURE_LEVEL_11_1;
    UINT flags = 0;
#if defined( DEBUG ) || defined( _DEBUG )
    flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    HRESULT hr;
    hr = D3D11CreateDevice
    (
        NULL,
        D3D_DRIVER_TYPE_HARDWARE,
        NULL,
        flags,
        NULL,
        0,
        D3D11_SDK_VERSION,
        m_Device.GetAddressOf(),
        &fl,
        m_DeviceContext.GetAddressOf()
    );

    assert(hr == S_OK);

    DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };
    swapChainDesc.BufferCount = 3;
    swapChainDesc.Width = 0;
    swapChainDesc.Height = 0;
    swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
    swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
    swapChainDesc.Stereo = FALSE;

    IDXGIFactory4* dxgiFactory = nullptr;
    IDXGISwapChain1* swapChainTemp = nullptr;
    hr = CreateDXGIFactory1(IID_PPV_ARGS(&dxgiFactory));
    assert(hr == S_OK);
    hr = dxgiFactory->CreateSwapChainForHwnd(m_Device.Get(), std::any_cast<HWND>(Application::GetInstance()->GetWindow()->GetNativeWindow()), &swapChainDesc, nullptr, nullptr, &swapChainTemp);
    assert(hr == S_OK);
    hr = swapChainTemp->QueryInterface(IID_PPV_ARGS(m_SwapChain.GetAddressOf()));
    assert(hr == S_OK);

    hr = dxgiFactory->EnumAdapters1(0, m_Adapter.GetAddressOf());
    assert(hr == S_OK);

#if 0
    auto adapterDescription = DXGI_ADAPTER_DESC1();
    m_Adapter->GetDesc1(&adapterDescription);
#endif

    swapChainTemp->Release();
    dxgiFactory->Release();
    m_SwapChain->SetMaximumFrameLatency(3);

    ID3D11Texture2D* pBackBuffer;
    m_SwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    hr = m_Device->CreateRenderTargetView(pBackBuffer, NULL, m_RenderTargetView.GetAddressOf());
    assert(hr == S_OK);
    pBackBuffer->Release();

    m_Viewport.TopLeftX = 0;
    m_Viewport.TopLeftY = 0;
    m_Viewport.Width = (float)Application::GetInstance()->GetWindow()->GetWidth();
    m_Viewport.Height = (float)Application::GetInstance()->GetWindow()->GetHeight();
    m_Viewport.MinDepth = .0f;
    m_Viewport.MaxDepth = 1.0f;
}

Satoshi::D3D11Context::~D3D11Context()
{
}

void Satoshi::D3D11Context::Present()
{
    m_SwapChain->Present(1, 0);
}

void Satoshi::D3D11Context::Update()
{
    m_DeviceContext->OMSetRenderTargets(1, m_RenderTargetView.GetAddressOf(), NULL);
    m_DeviceContext->ClearRenderTargetView(m_RenderTargetView.Get(), m_ClearColor);
}

void Satoshi::D3D11Context::SetClearColor(float r, float g, float b, float a)
{
    m_ClearColor[0] = r;
    m_ClearColor[1] = g;
    m_ClearColor[2] = b;
    m_ClearColor[3] = a;
}

std::any Satoshi::D3D11Context::GetImGUIData()
{
    D3D11ImGUIData data = {m_Device.Get(), m_DeviceContext.Get()};
    return data;
}
