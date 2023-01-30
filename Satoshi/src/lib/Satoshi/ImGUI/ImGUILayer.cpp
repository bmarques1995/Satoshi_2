#include "Satoshi/ImGUI/ImGUILayer.hpp"
#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_win32.h"

#include <Satoshi/Application.hpp>
#include <windows.h>

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

	ImGui_ImplWin32_Init(std::any_cast<HWND>(Application::GetInstance()->GetWindow()->GetNativeWindow()));
	ImGui_ImplOpenGL3_Init("#version 410");
}

void Satoshi::ImGUILayer::OnDetach()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void Satoshi::ImGUILayer::OnUpdate()
{
	ImGuiIO& io = ImGui::GetIO();
	auto app = Application::GetInstance();
	io.DisplaySize = ImVec2((float)app->GetWindow()->GetWidth(), (float)app->GetWindow()->GetHeight());

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Satoshi::ImGUILayer::OnEvent(Event& e)
{
}
