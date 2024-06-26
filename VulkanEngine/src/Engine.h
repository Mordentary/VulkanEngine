#pragma once

#include <optional>
#include <array>
#include <glm/glm.hpp>

#include "TimeHelper.h"
#include "Camera/Camera.h"
#include "Buffers/Buffer.h"
#include "Buffers/UniformBuffer.h"
#include "Images/Texture2D.h"

namespace vkEngine
{
	struct UniformBufferObject
	{
		glm::mat4 modelMat;
		glm::mat4 viewMat;
		glm::mat4 projMat;
	};

	class Application;

	class Engine
	{
	public:

		Engine(const Application* app);
		void run();
		const Application* getApp() const { return m_App; };
	public:
		static const uint32_t s_MaxFramesInFlight = 3;
		VkRenderPass m_RenderPass{ VK_NULL_HANDLE };
		const Shared<Instance>& getInstance() const { return m_Instance; };
	private:
		void update(Timestep deltaTime);
		void render();
		void cleanup();
		void init();
		void initInstance();

	private:
		const Application* m_App = nullptr;
		Scoped<Camera> m_Camera = nullptr;
		Shared<Instance> m_Instance = nullptr;

	private:
		void initVulkan();

		void initGraphicsPipeline();
		static std::vector<char> readFile(const std::string& filename);
		VkShaderModule createShaderModule(const std::vector<char>& code);

		void initRenderPass();

		void initBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
		//void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

		void initVertexBuffer();
		void initIndexBuffer();
		void initUniformBuffer();
		void initTextureImage();


		void updateUniformBuffer(uint32_t currentFrame, Timestep deltaTime);

		void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

		void initSyncObjects();
	private:

		void initDescriptorsSetLayout();
		void initDescriptorPool();
		void initDescriptorSets();

		VkDescriptorSetLayout m_DescriptorSetLayout;
		VkDescriptorPool m_DesciptorPool;
		std::vector<VkDescriptorSet> m_DescriptorSets;

		//DEBUG FUNC
		void updateTexture(VkDescriptorSet descriptorSet, uint32_t binding);
		float m_LastUpdateTime = 0.0f;


		void modelInit();
		std::vector<Vertex> vertices{};
		std::vector<uint32_t> indices{};
		const std::string MODEL_PATH = "assets/models/viking_room.obj";
		const std::string TEXTURE_PATH = "assets/textures/viking_room.png";


		VkPipeline m_GraphicsPipeline;
		VkPipelineLayout m_PipelineLayout{ VK_NULL_HANDLE };



		Shared<Texture2D> m_TextureTest{ nullptr }, m_TextureTest2{ nullptr }, m_CurrentTexture{ nullptr };

		Scoped<VertexBuffer> m_VertexBuffer{ nullptr };
		Scoped<IndexBuffer> m_IndexBuffer{ nullptr };

		std::vector<Shared<UniformBuffer>> m_UniformBuffers{};



		//VkImage m_DepthImage;
		//VkDeviceMemory m_DepthImageMemory;
		//VkImageView m_DepthImageView;

		std::vector<VkSemaphore> m_RenderFinishedSemaphores{};
		std::vector<VkFence> m_InFlightFences{};
	};
}
