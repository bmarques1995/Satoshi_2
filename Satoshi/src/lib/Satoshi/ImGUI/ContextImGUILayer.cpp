#include "Satoshi/ImGUI/ContextImGUILayer.hpp"
#include "Platform/Graphics/GL4/GL4ImGUILayer.hpp"
#include "Platform/Graphics/VK/VKImGUILayer.hpp"
#ifdef ST_PLATFORM_WINDOWS
#include "Platform/Graphics/D3D11/D3D11ImGUILayer.hpp"
#include "Platform/Graphics/D3D12/D3D12ImGUILayer.hpp"
#endif
Satoshi::ContextImGUILayer* Satoshi::ContextImGUILayer::Create(GRAPHICS_API api)
{
	switch (api)
	{
	case Satoshi::GRAPHICS_API::GL4:
		return new GL4ImGUILayer();
	case Satoshi::GRAPHICS_API::VK:
		return new VKImGUILayer();
#ifdef ST_PLATFORM_WINDOWS
	case Satoshi::GRAPHICS_API::D3D11:
		return new D3D11ImGUILayer();
	case Satoshi::GRAPHICS_API::D3D12:
		return new D3D12ImGUILayer();
#endif
	default:
		return nullptr;
	}
	
}
