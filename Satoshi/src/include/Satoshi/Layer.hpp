#ifndef LAYER_HPP
#define LAYER_HPP

#include <stpch.hpp>
#include "Events/Event.hpp"

namespace Satoshi
{
    class SATOSHI_API Layer
    {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer();

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate() {}
        virtual void OnEvent(Event& e) {}

        inline const std::string& GetName() const { return m_DebugName; }
    private:
        std::string m_DebugName;
    };
}


#endif //LAYER_HPP
