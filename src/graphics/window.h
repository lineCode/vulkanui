#ifndef VULKANUI_WINDOW_H
#define VULKANUI_WINDOW_H

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>
#include <iostream>

namespace VulkanUI {
    class Window {
    public:
        Window();
        ~Window();
        inline bool ShouldClose () {
            return glfwWindowShouldClose(window);
        }
        inline void Poll () {
            glfwPollEvents();
        }
        GLFWwindow* window;
    };
};

#endif //VULKANUI_WINDOW_H
