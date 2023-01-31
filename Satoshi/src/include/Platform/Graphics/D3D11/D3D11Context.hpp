#ifdef ST_PLATFORM_WINDOWS

#ifndef D3D11_CONTEXT_HPP
#define D3D11_CONTEXT_HPP

#include "Satoshi/Renderer/GraphicsContext.hpp"

#include <d3d11_4.h>
#include <dxgi.h>

#include <wrl.h>

using Microsoft::WRL::ComPtr;

namespace Satoshi
{
    struct D3D11ImGUIData
    {
        ID3D11Device* Device;
        ID3D11DeviceContext* DeviceContext;
    };
    class D3D11Context : public GraphicsContext
    {
    public:
        D3D11Context();
        ~D3D11Context();

        virtual void Present() override;
        virtual void Update() override;

        virtual void SetClearColor(float r, float g, float b, float a) override;
        virtual std::any GetImGUIData() override;
    private:
        float m_ClearColor[4];

        ComPtr<ID3D11Device> m_Device;
        ComPtr<ID3D11DeviceContext> m_DeviceContext;
        ComPtr<IDXGISwapChain3> m_SwapChain;
        ComPtr<IDXGIAdapter1> m_Adapter;
        ComPtr<ID3D11RenderTargetView> m_RenderTargetView;

        D3D11_VIEWPORT m_Viewport;
    };
}


#endif //D3D11_CONTEXT_HPP

#endif //ST_PLATFORM_WINDOWS
