#ifndef WIN32_IMGUI_LAYER_HPP
#define WIN32_IMGUI_LAYER_HPP

#include "Satoshi/ImGUI/WindowImGUILayer.hpp"

namespace Satoshi
{
    class Win32ImGUILayer : public WindowImGUILayer
    {
    public:
        Win32ImGUILayer();
        ~Win32ImGUILayer();

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnUpdate() override;
        virtual void OnEvent(Event& e) override;

        virtual void BeginFrame() override;
        virtual void EndFrame() override;
    private:
        bool show_demo_window = true;
    };
}


#endif //IMGUI_LAYER_HPP
