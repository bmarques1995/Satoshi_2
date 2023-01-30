#include "ExampleLayer.hpp"

ExampleLayer::ExampleLayer() :
	Satoshi::Layer("Example")
{
}

ExampleLayer::~ExampleLayer()
{
}

void ExampleLayer::OnUpdate()
{
	if(Satoshi::Input::IsKeyPressed(ST_KEY_A))
		Satoshi::Console::Debug("Testing the input");
}

void ExampleLayer::OnEvent(Satoshi::Event& e)
{
	//Satoshi::Console::Log("{0}", e);
}
