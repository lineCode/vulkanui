#include <iostream>

#include "graphics/window.h"
#include "graphics/vulkan.h"

using namespace VulkanUI;

int main() {

    std::cout << "Hello world " << std::endl;

    Window * window = new Window();
    Vulkan * vulkan = new Vulkan(window);

    while (!window->ShouldClose()) {
        window->Poll();
		vulkan->DrawFrame();
    }

    delete window;
    delete vulkan;

    return 0;
}