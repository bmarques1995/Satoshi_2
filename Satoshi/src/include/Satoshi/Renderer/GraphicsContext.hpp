#ifndef GRAPHICS_CONTEXT_HPP
#define GRAPHICS_CONTEXT_HPP

#include <stpch.hpp>
#include "Satoshi/Core/Core.hpp"
#include "Satoshi/Events/ApplicationEvent.hpp"
#include "Satoshi/Renderer/RendererAPI.hpp"

namespace Satoshi
{
    class SATOSHI_API GraphicsContext
    {
    public:
        virtual void ClearTarget() = 0;
        virtual void SetClearColor(float r, float g, float b, float a) = 0;
        virtual void ReceiveCommands() = 0;
        virtual void DispatchCommands() = 0;
        virtual void Draw(uint32_t elements) = 0;
        virtual void NewFrame() = 0;
        virtual void EndFrame() = 0;
        virtual void Present() = 0;

        virtual void OnResize(WindowResizeEvent&) = 0;

        virtual std::any GetImGUIData() = 0;

        static GraphicsContext* Create(GRAPHICS_API api);
    };
}


#endif //GRAPHICS_CONTEXT_HPP
