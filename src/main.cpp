#include <iostream>

#include "graphics/window.h"
#include "graphics/vulkan.h"

using namespace VulkanUI;

Window * window;
Vulkan * vulkan;

void onWindowResized(GLFWwindow* window, int width, int height) {
	Window* app = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
	vulkan->recreateSwapChain();
}

int main() {

    std::cout << "Hello world " << std::endl;

    window = new Window();
    vulkan = new Vulkan(window);
	glfwSetWindowSizeCallback(window->window, onWindowResized);

    while (!window->ShouldClose()) {
        window->Poll();
		vulkan->DrawFrame();
    }

	vulkan->Terminate();
	delete vulkan;
    delete window;

    return 0;
}