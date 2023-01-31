#include "Satoshi/ImGUI/ImGUILayer.hpp"
#include "imgui.h"
#include <Satoshi/Core/Application.hpp>

Satoshi::ImGUILayer::ImGUILayer() :
	Layer("ImGUI Layer")
{
}

Satoshi::ImGUILayer::~ImGUILayer()
{
}

void Satoshi::ImGUILayer::OnAttach()
{
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGuiIO& io = ImGui::GetIO();

	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;

	
}

void Satoshi::ImGUILayer::OnDetach()
{
	
	ImGui::DestroyContext();
}

void Satoshi::ImGUILayer::OnUpdate()
{
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);
}

void Satoshi::ImGUILayer::OnEvent(Event& e)
{
	
}

void Satoshi::ImGUILayer::BeginFrame()
{
	ImGui::NewFrame();
}

void Satoshi::ImGUILayer::EndFrame()
{
	ImGuiIO& io = ImGui::GetIO();
	auto app = Application::GetInstance();
	io.DisplaySize = ImVec2((float)app->GetWindow()->GetWidth(), (float)app->GetWindow()->GetHeight());

	ImGui::Render();
}
