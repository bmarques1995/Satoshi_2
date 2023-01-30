#ifndef IMGUI_LAYER_HPP
#define IMGUI_LAYER_HPP

#include "Satoshi/Layer.hpp"

namespace Satoshi
{
    class ImGUILayer : public Layer
    {
    public:
        ImGUILayer();
        ~ImGUILayer();

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnUpdate() override;
        virtual void OnEvent(Event& e) override;

    private:
        bool show_demo_window = true;
    };
}


#endif //IMGUI_LAYER_HPP
