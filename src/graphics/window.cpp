#include "graphics/window.h"
#include "config.h"

namespace VulkanUI {
    Window::Window() {
        if (!glfwInit())  {
            std::cout << "GLFW init failed" << std::endl;
        } else {
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

            window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "My Title", NULL, NULL);
            if (!window)  {
                std::cout << "GLFW window init falied" << std::endl;
                return;
            }

			glfwSetWindowUserPointer(window, this);
			// glfwSetWindowSizeCallback(window, HelloTriangleApplication::onWindowResized);

            if (!glfwVulkanSupported()) {
                std::cout << "Vulkan not supported" << std::endl;
                return;
            }
        }
    }

    Window::~Window() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
}
