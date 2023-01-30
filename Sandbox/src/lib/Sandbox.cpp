#include <Satoshi.hpp>

class Sandbox : public Satoshi::Application
{
public:
	Sandbox()
	{
	
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
