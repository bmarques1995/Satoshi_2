#include "Platform/Graphics/VK/VKImGUILayer.hpp"
#include "imgui.h"
#include "backends/imgui_impl_vulkan.h"

#include <Satoshi/Core/Application.hpp>

Satoshi::VKImGUILayer::VKImGUILayer()
{
}

Satoshi::VKImGUILayer::~VKImGUILayer()
{
}

void Satoshi::VKImGUILayer::OnAttach()
{
	m_Data = std::any_cast<VKImGUIData>(Application::GetInstance()->GetContext()->GetImGUIData());
	ImGui_ImplVulkan_Init(&m_Data.VulkanInfo, m_Data.RenderPass);

    VkCommandPool command_pool = m_Data.CommandPool;
    VkCommandBuffer command_buffer = m_Data.CommandBuffer;

    VkResult vk_r = vkResetCommandPool(m_Data.VulkanInfo.Device, command_pool, 0);
    assert(vk_r == VK_SUCCESS);
    VkCommandBufferBeginInfo begin_info = {};
    begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    begin_info.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    vk_r = vkBeginCommandBuffer(command_buffer, &begin_info);
    assert(vk_r == VK_SUCCESS);

    ImGui_ImplVulkan_CreateFontsTexture(command_buffer);

    VkSubmitInfo end_info = {};
    end_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    end_info.commandBufferCount = 1;
    end_info.pCommandBuffers = &command_buffer;
    vk_r = vkEndCommandBuffer(command_buffer);
    assert(vk_r == VK_SUCCESS);
    vk_r = vkQueueSubmit(m_Data.VulkanInfo.Queue, 1, &end_info, VK_NULL_HANDLE);
    assert(vk_r == VK_SUCCESS);

    vk_r = vkDeviceWaitIdle(m_Data.VulkanInfo.Device);
    assert(vk_r == VK_SUCCESS);
    ImGui_ImplVulkan_DestroyFontUploadObjects();
}

void Satoshi::VKImGUILayer::OnDetach()
{
	ImGui_ImplVulkan_Shutdown();
}

void Satoshi::VKImGUILayer::OnUpdate()
{
}

void Satoshi::VKImGUILayer::OnEvent(Event& e)
{
}

void Satoshi::VKImGUILayer::BeginFrame()
{
	ImGui_ImplVulkan_NewFrame();
}

void Satoshi::VKImGUILayer::EndFrame()
{
	ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), m_Data.CommandBuffer);
}
