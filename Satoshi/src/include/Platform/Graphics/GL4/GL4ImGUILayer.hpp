#ifndef GL4_IMGUI_LAYER_HPP
#define GL4_IMGUI_LAYER_HPP

#include "Satoshi/ImGUI/ContextImGUILayer.hpp"
#include "Platform/Graphics/GL4/GL4Context.hpp"

namespace Satoshi
{
    class GL4ImGUILayer : public ContextImGUILayer
    {
    public:
        GL4ImGUILayer();
        ~GL4ImGUILayer();

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnUpdate() override;
        virtual void OnEvent(Event& e) override;

        virtual void BeginFrame() override;
        virtual void EndFrame() override;
    private:

    };
}


#endif //GL4_IMGUI_LAYER_HPP
