#ifndef GRAPHICS_CONTEXT_HPP
#define GRAPHICS_CONTEXT_HPP

#include <stpch.hpp>
#include "Satoshi/Core/Core.hpp"

namespace Satoshi
{
    class SATOSHI_API GraphicsContext
    {
    public:

        virtual void Present() = 0;
        virtual void Update() = 0;

        virtual void SetClearColor(float r, float g, float b, float a) = 0;

        virtual std::any GetImGUIData() = 0;
    };
}


#endif //GRAPHICS_CONTEXT_HPP
