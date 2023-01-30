#ifndef CONTEXT_IMGUI_LAYER_HPP
#define CONTEXT_IMGUI_LAYER_HPP

#include "ImGUILayer.hpp"

namespace Satoshi
{
    class ContextImGUILayer : public ImGUILayer
    {
    public:
        virtual void OnAttach() = 0;
        virtual void OnDetach() = 0;
        virtual void OnUpdate() = 0;
        virtual void OnEvent(Event& e) = 0;

        virtual void BeginFrame() = 0;
        virtual void EndFrame() = 0;
    };
}


#endif //WINDOW_IMGUI_LAYER_HPP