
#ifndef VULKANUI_VULKAN_H
#define VULKANUI_VULKAN_H

#include<vector>

#include "graphics/window.h"

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

namespace VulkanUI {
    class Vulkan {
    public:
        Vulkan (Window * window);
        void Terminate ();

		void DrawFrame ();
    private:
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
		VkPipelineLayout pipelineLayout;

		VkPipeline graphicsPipeline;

		std::vector<VkFramebuffer> swapChainFramebuffers;

		VkCommandPool commandPool;
		std::vector<VkCommandBuffer> commandBuffers;

		VkSemaphore imageAvailableSemaphore;
		VkSemaphore renderFinishedSemaphore;

        void createInstance ();
        bool checkValidationLayerSupport ();
        void setupDebugCallback ();

		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
		bool isDeviceSuitable(VkPhysicalDevice device);
		int rateDeviceSuitability(VkPhysicalDevice device);
        void pickPhysicalDevice ();
        void createLogicalDevice ();

		void createSurface (GLFWwindow * window);

		SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
		void createSwapChain ();
		void createImageViews();

		void createRenderPass ();
		void createGraphicsPipeline ();
		VkShaderModule createShaderModule (const std::vector<char>& code);

		void createFramebuffers ();
		void createCommandPool ();
		void createCommandBuffers ();

		void createSemaphores();
	};
}


#endif //VULKANUI_VULKAN_H
