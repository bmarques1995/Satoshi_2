#include "Satoshi/Renderer/GraphicsContext.hpp"
#include "Platform/Graphics/GL4/GL4Context.hpp"
#include "Platform/Graphics/D3D11/D3D11Context.hpp"

Satoshi::GraphicsContext* Satoshi::GraphicsContext::Create(GRAPHICS_API api)
{
	switch (api)
	{
	case Satoshi::GRAPHICS_API::GL4:
		return new GL4Context();
	case Satoshi::GRAPHICS_API::D3D11:
		return new D3D11Context();
		/*case Satoshi::GRAPHICS_API::VK:
			break;
		case Satoshi::GRAPHICS_API::D3D12:
			break;*/
	default:
		return nullptr;
	}
}
