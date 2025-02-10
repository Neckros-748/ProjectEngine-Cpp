#pragma once
#include "window/Window.h"
#include "console/Console.h"



namespace __system {

    bool __initialize__(int width, int height, const std::string& title)
    {
        if (!Window::Init(width, height, title)) {
            Console::error("Initialization failed.", { "Failed to initialize the window." });
            return false;
        }

        return true;
    }

    void __terminate__()
    {
        Window::Terminate();
    }

}