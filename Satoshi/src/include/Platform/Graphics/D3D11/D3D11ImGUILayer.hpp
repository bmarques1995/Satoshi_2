#ifdef ST_PLATFORM_WINDOWS

#ifndef D3D11_IMGUI_LAYER_HPP
#define D3D11_IMGUI_LAYER_HPP

#include "Satoshi/ImGUI/ContextImGUILayer.hpp"
#include "Platform/Graphics/D3D11/D3D11Context.hpp"

namespace Satoshi
{
    class D3D11ImGUILayer : public ContextImGUILayer
    {
    public:
        D3D11ImGUILayer();
        ~D3D11ImGUILayer();

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnUpdate() override;
        virtual void OnEvent(Event& e) override;

        virtual void BeginFrame() override;
        virtual void EndFrame() override;

    private:

    };
}


#endif //D3D11_IMGUI_LAYER_HPP

#endif //ST_PLATFORM_WINDOWS
