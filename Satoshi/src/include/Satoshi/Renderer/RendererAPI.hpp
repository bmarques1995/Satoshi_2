#ifndef RENDERER_API_HPP
#define RENDERER_API_HPP

#include <stpch.hpp>

namespace Satoshi
{
    enum class GRAPHICS_API
    { 
        GL4 = 1,
        D3D11,
        VK,
        D3D12
    };

	class RendererAPI
	{
    public:
        static GRAPHICS_API MatchAPIByName(std::string_view name);
	private:
        static std::unordered_map<std::string_view, GRAPHICS_API> s_APINamesMapper;
	};

}

#endif //RENDERER_API_HPP
