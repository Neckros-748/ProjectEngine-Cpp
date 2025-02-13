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

        if (Event::Keyboard::isPress(GLFW_KEY_ESCAPE)) {
            Window::setShouldClose(true);
        }
        if (Event::Keyboard::isPress(GLFW_KEY_TAB)) {
            Event::Mouse::isLocked() ? Event::Mouse::setLock(false) : Event::Mouse::setLock(true);
        }

        //glm::vec2 pos = Event::Mouse::getPosition();
        //std::cout << pos.x << ", " << pos.y << std::endl;

        Window::swapBuffer();
        Event::poll();
    }

    __terminate__();
    return 0;
}



