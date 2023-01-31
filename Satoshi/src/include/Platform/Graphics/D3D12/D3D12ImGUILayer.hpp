#ifdef ST_PLATFORM_WINDOWS

#ifndef D3D12_IMGUI_LAYER_HPP
#define D3D12_IMGUI_LAYER_HPP

#include "Satoshi/ImGUI/ContextImGUILayer.hpp"
#include "Platform/Graphics/D3D12/D3D12Context.hpp"

namespace Satoshi
{
    class D3D12ImGUILayer : public ContextImGUILayer
    {
    public:
        D3D12ImGUILayer();
        ~D3D12ImGUILayer();

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnUpdate() override;
        virtual void OnEvent(Event& e) override;

        virtual void BeginFrame() override;
        virtual void EndFrame() override;
    private:
        D3D12ImGUIData m_Data;
    };
}


#endif //D3D12_IMGUI_LAYER_HPP


#endif
