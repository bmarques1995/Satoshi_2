#ifndef GL4_CONTEXT_HPP
#define GL4_CONTEXT_HPP

#include "Satoshi/Renderer/GraphicsContext.hpp"

#include <glad/wgl.h>

namespace Satoshi
{
    class GL4Context : public GraphicsContext
    {
    public:
        GL4Context();
        ~GL4Context();

        virtual void Present() override;
        virtual void Update() override;

        virtual void SetClearColor(float r, float g, float b, float a) override;
        virtual std::any GetImGUIData() override;
    private:
        float m_ClearColor[4];

        std::string m_GLSLImGUIVersion;

        HDC m_HDC;
        HGLRC m_HRC;
        PFNWGLSWAPINTERVALEXTPROC SwapIntervalEXT;
    };
}


#endif //GL4_CONTEXT_HPP
