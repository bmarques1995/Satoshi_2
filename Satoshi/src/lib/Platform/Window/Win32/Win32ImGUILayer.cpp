#include "Platform/Window/Win32/Win32ImGUILayer.hpp"
#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_win32.h"

#include <Satoshi/Core/Application.hpp>
#include <windows.h>

Satoshi::Win32ImGUILayer::Win32ImGUILayer()
{
}

Satoshi::Win32ImGUILayer::~Win32ImGUILayer()
{
}

void Satoshi::Win32ImGUILayer::OnAttach()
{
	ImGui_ImplWin32_Init(std::any_cast<HWND>(Application::GetInstance()->GetWindow()->GetNativeWindow()));
	
}

void Satoshi::Win32ImGUILayer::OnDetach()
{
	
	ImGui_ImplWin32_Shutdown();
}

void Satoshi::Win32ImGUILayer::OnUpdate()
{
	
}

void Satoshi::Win32ImGUILayer::OnEvent(Event& e)
{
}

void Satoshi::Win32ImGUILayer::BeginFrame()
{
	ImGui_ImplWin32_NewFrame();
	
}

void Satoshi::Win32ImGUILayer::EndFrame()
{
	
}
