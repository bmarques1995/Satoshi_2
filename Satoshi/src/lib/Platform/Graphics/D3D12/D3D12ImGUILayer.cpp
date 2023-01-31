#ifdef ST_PLATFORM_WINDOWS

#include "Platform/Graphics/D3D12/D3D12ImGUILayer.hpp"
#include "imgui.h"
#include "backends/imgui_impl_dx12.h"

#include <Satoshi/Core/Application.hpp>

Satoshi::D3D12ImGUILayer::D3D12ImGUILayer()
{
}

Satoshi::D3D12ImGUILayer::~D3D12ImGUILayer()
{
}

void Satoshi::D3D12ImGUILayer::OnAttach()
{
	m_Data = std::any_cast<D3D12ImGUIData>(Application::GetInstance()->GetContext()->GetImGUIData());
	ImGui_ImplDX12_Init(m_Data.Device, m_Data.NumFramesInFlight, m_Data.RTVFormat, m_Data.DescriptorHeap, m_Data.DescriptorHeap->GetCPUDescriptorHandleForHeapStart(), m_Data.DescriptorHeap->GetGPUDescriptorHandleForHeapStart());
}

void Satoshi::D3D12ImGUILayer::OnDetach()
{
	ImGui_ImplDX12_Shutdown();
}

void Satoshi::D3D12ImGUILayer::OnUpdate()
{
}

void Satoshi::D3D12ImGUILayer::OnEvent(Event& e)
{
}

void Satoshi::D3D12ImGUILayer::BeginFrame()
{
	ImGui_ImplDX12_NewFrame();
}

void Satoshi::D3D12ImGUILayer::EndFrame()
{
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), m_Data.CommandList);
}

#endif // ST_PLATFORM_WINDOWS