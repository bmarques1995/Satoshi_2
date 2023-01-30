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
	Satoshi::Console::Debug("New Extern Layer");
}

void ExampleLayer::OnEvent(Satoshi::Event& e)
{
	//Satoshi::Console::Log("{0}", e);
}
