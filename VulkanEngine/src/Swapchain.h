#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <cstdint>
#include <vector>
#include <algorithm>
#include "Core.h"

namespace vkEngine
{
	class Window;
	class VulkanContext;
	class LogicalDevice;
	class QueueHandler;
	class PhysicalDevice;
	class DepthImage;
	class Image2D;


	struct QueueFamilyIndices;

	struct SwapChainSupportDetails
	{
		VkSurfaceCapabilitiesKHR capabilities{};
		std::vector<VkSurfaceFormatKHR> formats{};
		std::vector<VkPresentModeKHR> presentModes{};
	};

	class Swapchain
	{
		friend Window;

	public:
		Swapchain(const Shared<Window>& window, VkSurfaceKHR surface, Shared<LogicalDevice>& device, Shared<PhysicalDevice>& physicalD, Shared<QueueHandler>& qHandler, uint32_t maxFramesInFlight);
		Swapchain() = delete;
		~Swapchain();
		void resize(uint32_t newWidth, uint32_t newHeight);
		VkResult acquireNextImage(uint32_t frame);
		void present(VkSemaphore* signalSemaphores, uint32_t count);
		void recreateSwapchain(VkRenderPass renderpass);
		void cleanupSwapchain();



		const Scoped<Image2D>& getMSAABuffer() const { return m_MultisampledColorBuffer; }
		const Scoped<DepthImage>& getDepthBuffer() const { return m_DepthBuffer; }
		VkSemaphore getImageSemaphore(uint32_t frame) { return m_ImageAvailableSemaphores[frame]; }
		VkFormat getImagesFormat() const { return m_SwapchainImageFormat; }
		VkExtent2D getExtent() const { return m_SwapchainExtent; }
		VkFramebuffer getFramebuffer(uint32_t index) const { return m_SwapchainFramebuffers[index]; }
		void initFramebuffers(VkRenderPass renderpass);
		uint32_t getImageIndex() const { return m_ImageIndex; }
	private:
		void initSwapchain();
		void initImageViews();
		void initSemaphores();
		void initDepthBuffer();
		void initMSAAColorBuffer();

		VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& abailableModes);
		VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

	private:
		const Shared<Window> m_Window;
		const Shared<QueueHandler> m_QueueHandler;
		const Shared<PhysicalDevice> m_PhysicalDevice;
		const Shared<LogicalDevice> m_Device;

	private:
		VkSurfaceKHR m_Surface = nullptr;
		VkSwapchainKHR m_Swapchain = nullptr;
		std::vector<VkSemaphore> m_ImageAvailableSemaphores{};
		std::vector<VkFramebuffer> m_SwapchainFramebuffers{};
		Scoped<DepthImage> m_DepthBuffer;
		Scoped<Image2D> m_MultisampledColorBuffer;


		//TODO: should I go with different image class aka swapchainImage?
		std::vector<VkImage> m_SwapchainImages{};
		std::vector<VkImageView> m_SwapchainImageViews{};
		VkFormat m_SwapchainImageFormat{};
		VkExtent2D m_SwapchainExtent{};

		uint32_t m_ImageIndex;
		const uint32_t m_MaxFramesInFlight;

		uint32_t m_Width = 1000, m_Height = 1000;
	};
}
