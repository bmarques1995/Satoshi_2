#ifdef ST_PLATFORM_WINDOWS

#include "Platform/Graphics/D3D11/D3D11ImGUILayer.hpp"
#include "imgui.h"
#include "backends/imgui_impl_dx11.h"

#include <Satoshi/Core/Application.hpp>

Satoshi::D3D11ImGUILayer::D3D11ImGUILayer()
{
}

Satoshi::D3D11ImGUILayer::~D3D11ImGUILayer()
{
}

void Satoshi::D3D11ImGUILayer::OnAttach()
{
	D3D11ImGUIData m_Data = std::any_cast<D3D11ImGUIData>(Application::GetInstance()->GetContext()->GetImGUIData());
	ImGui_ImplDX11_Init(m_Data.Device, m_Data.DeviceContext);
}

void Satoshi::D3D11ImGUILayer::OnDetach()
{
	ImGui_ImplDX11_Shutdown();
}

void Satoshi::D3D11ImGUILayer::OnUpdate()
{
}

void Satoshi::D3D11ImGUILayer::OnEvent(Event& e)
{
}

void Satoshi::D3D11ImGUILayer::BeginFrame()
{
	ImGui_ImplDX11_NewFrame();
}

void Satoshi::D3D11ImGUILayer::EndFrame()
{
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

#endif
