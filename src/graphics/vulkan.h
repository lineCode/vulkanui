
#ifndef VULKANUI_VULKAN_H
#define VULKANUI_VULKAN_H

#include <vector>
#include <array>

#include "graphics/window.h"

#define GLM_FORCE_RADIANS
#include "external/glm/glm.hpp"
#include "external/glm/gtc/matrix_transform.hpp"
#include <chrono>

struct QueueFamilyIndices {
	int graphicsFamily = -1;
	int presentFamily = -1;

	bool isComplete() {
		return graphicsFamily >= 0 && presentFamily >= 0;
	}
};

struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

struct Vertex {
	glm::vec2 pos;
	glm::vec3 color;

	static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {
		/* As the function prototype indicates, there are going to be two of these structures.
		 * An attribute description struct describes how to extract a vertex attribute from a
		 * chunk of vertex data originating from a binding description. We have two attributes,
		 * position and color, so we need two attribute description structs. */
		std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions = {};
		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(Vertex, pos);

		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Vertex, color);

		return attributeDescriptions;
	}

	static VkVertexInputBindingDescription getBindingDescription() {
		VkVertexInputBindingDescription bindingDescription = {};
		bindingDescription.binding = 0;
		bindingDescription.stride = sizeof(Vertex);
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		return bindingDescription;
	}
};
/* const std::vector<Vertex> vertices = {
		{{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
		{{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
		{{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
}; */
const std::vector<Vertex> vertices = {
		{{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
		{{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
		{{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
		{{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}
};
// uint32_t for more then 65535 verts
const std::vector<uint16_t> indices = {
		0, 1, 2, 2, 3, 0
};

struct UniformBufferObject {
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 proj;
};

namespace VulkanUI {
    class Vulkan {
    public:
        Vulkan (Window * window);
        void Terminate ();

		void updateUniformBuffer();
		void DrawFrame ();
		void recreateSwapChain ();
    private:
		Window * theWindow;

        VkInstance instance;
        VkDebugReportCallbackEXT callback;

        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

        VkDevice device;
        VkQueue graphicsQueue;

        VkSurfaceKHR surface;
		VkQueue presentQueue;

		VkSwapchainKHR swapChain;
		std::vector<VkImage> swapChainImages;
		VkFormat swapChainImageFormat;
		VkExtent2D swapChainExtent;

		std::vector<VkImageView> swapChainImageViews;

		VkRenderPass renderPass;
		VkDescriptorSetLayout descriptorSetLayout;
		VkPipelineLayout pipelineLayout;

		VkPipeline graphicsPipeline;

		std::vector<VkFramebuffer> swapChainFramebuffers;

		VkCommandPool commandPool;
		std::vector<VkCommandBuffer> commandBuffers;

		VkSemaphore imageAvailableSemaphore;
		VkSemaphore renderFinishedSemaphore;

		VkBuffer vertexBuffer;
		VkDeviceMemory vertexBufferMemory;
		VkBuffer indexBuffer;
		VkDeviceMemory indexBufferMemory;
		VkBuffer uniformBuffer;
		VkDeviceMemory uniformBufferMemory;

		VkDescriptorPool descriptorPool;
		VkDescriptorSet descriptorSet;

        void createInstance ();
        bool checkValidationLayerSupport ();
        void setupDebugCallback ();

		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
		bool isDeviceSuitable(VkPhysicalDevice device);
		int rateDeviceSuitability(VkPhysicalDevice device);
        void pickPhysicalDevice ();
        void createLogicalDevice ();

		void createSurface ();

		SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
		VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
		void createSwapChain ();
		void createImageViews();

		void createRenderPass ();

		void createDescriptorSetLayout ();
		void createGraphicsPipeline ();
		VkShaderModule createShaderModule (const std::vector<char>& code);

		void createFramebuffers ();
		void createCommandPool ();
		void createCommandBuffers ();

		void createSemaphores();

		void cleanupSwapChain ();

		void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
		void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
		void createVertexBuffer ();
		void createIndexBuffer ();
		void createUniformBuffer ();

		void createDescriptorPool ();
		void createDescriptorSet ();

		uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
	};
}


#endif //VULKANUI_VULKAN_H
