#pragma once
#include "window/Window.h"
#include "event/Event.h"
#include "console/Console.h"



namespace __system {

    bool __initialize__(int width, int height, const std::string& title)
    {
        if (!Window::Init(width, height, title)) {
            Window::Terminate();
            Console::error("Initialization failed.", { "Failed to initialize the window." });
            return false;
        }

        if (!Event::Init(Window::getWindow())) {
            Window::Terminate();
            Event::Terminate();
            Console::error("Initialization failed.", { "Failed to initialize the event system." });
            return false;
        }

        return true;
    }

    void __terminate__()
    {
        Window::Terminate();
        Event::Terminate();
    }

}