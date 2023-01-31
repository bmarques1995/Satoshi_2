#ifndef VK_IMGUI_LAYER_HPP
#define VK_IMGUI_LAYER_HPP

#include "Satoshi/ImGUI/ContextImGUILayer.hpp"
#include "Platform/Graphics/VK/VKContext.hpp"

namespace Satoshi
{
    class VKImGUILayer : public ContextImGUILayer
    {
    public:
        VKImGUILayer();
        ~VKImGUILayer();

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnUpdate() override;
        virtual void OnEvent(Event& e) override;

        virtual void BeginFrame() override;
        virtual void EndFrame() override;
    private:
        VKImGUIData m_Data;
    };
}


#endif //VK_IMGUI_LAYER_HPP
