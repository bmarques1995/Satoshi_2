#include "Platform/Graphics/GL4/GL4ImGUILayer.hpp"
#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"

#include <Satoshi/Core/Application.hpp>

Satoshi::GL4ImGUILayer::GL4ImGUILayer()
{
}

Satoshi::GL4ImGUILayer::~GL4ImGUILayer()
{
}

void Satoshi::GL4ImGUILayer::OnAttach()
{
	std::string data = std::any_cast<std::string>(Application::GetInstance()->GetContext()->GetImGUIData());
	ImGui_ImplOpenGL3_Init(data.c_str());
}

void Satoshi::GL4ImGUILayer::OnDetach()
{
	ImGui_ImplOpenGL3_Shutdown();
}

void Satoshi::GL4ImGUILayer::OnUpdate()
{
}

void Satoshi::GL4ImGUILayer::OnEvent(Event& e)
{
}

void Satoshi::GL4ImGUILayer::BeginFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
}

void Satoshi::GL4ImGUILayer::EndFrame()
{
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
