#include <Satoshi/Core/Entrypoint.hpp>
#include "ExampleLayer.hpp"

class Sandbox : public Satoshi::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox()
	{
	
	}

private:

};


Satoshi::Application* Satoshi::CreateApplication()
{
	return new Sandbox();
}
