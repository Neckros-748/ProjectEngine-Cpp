#include <iostream>

#include "system/system.hpp"



bool __initialize__(int argc, char** argv)
{
    if (!__system::__initialize__(1000, 1000, "Window : ProjectEngine-Cpp")) {
        return false;
    }

    Console::info("Initialization successful.", { "All systems initialized successfully." });
    return true;
}

void __terminate__()
{
    __system::__terminate__();
}



int main(int argc, char** argv)
{
    if (!__initialize__(argc, argv)) {
        return 1;
    }

    while (!Window::isShouldClose()) {
        Window::clear();

        Window::swapBuffer();
        glfwPollEvents();
    }

    __terminate__();
    return 0;
}