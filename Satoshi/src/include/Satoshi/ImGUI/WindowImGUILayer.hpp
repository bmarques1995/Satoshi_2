#ifndef WINDOW_IMGUI_LAYER_HPP
#define WINDOW_IMGUI_LAYER_HPP

#include "ImGUILayer.hpp"
#include "Satoshi/Renderer/RendererAPI.hpp"

namespace Satoshi
{
    class WindowImGUILayer : public ImGUILayer
    {
    public:

        virtual void OnAttach() = 0;
        virtual void OnDetach() = 0;
        virtual void OnUpdate() = 0;
        virtual void OnEvent(Event& e) = 0;

        virtual void BeginFrame() = 0;
        virtual void EndFrame() = 0;

        static WindowImGUILayer* Create();
    };
}


#endif //WINDOW_IMGUI_LAYER_HPP