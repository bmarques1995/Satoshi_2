#include "Satoshi/ImGUI/ContextImGUILayer.hpp"
#include "Platform/Graphics/GL4/GL4ImGUILayer.hpp"
#ifdef ST_PLATFORM_WINDOWS
#include "Platform/Graphics/D3D11/D3D11ImGUILayer.hpp"
#endif
Satoshi::ContextImGUILayer* Satoshi::ContextImGUILayer::Create(GRAPHICS_API api)
{
	switch (api)
	{
	case Satoshi::GRAPHICS_API::GL4:
		return new GL4ImGUILayer();
#ifdef ST_PLATFORM_WINDOWS
	case Satoshi::GRAPHICS_API::D3D11:
		return new D3D11ImGUILayer();
#endif
	/*case Satoshi::GRAPHICS_API::VK:
		break;
	case Satoshi::GRAPHICS_API::D3D12:
		break;*/
	default:
		return nullptr;
	}
	
}
