#pragma once
#include <string>
#include <glad/glad.h>
#include <glfw/glfw3.h>



class Window {
private:
    static GLFWwindow* window;
    static int         width;
    static int         height;

    friend class Event;

public:
    static bool Init(int width, int height, const std::string& title);
    static void Terminate();

    static void swapBuffer();
    static void clear();

    static GLFWwindow* getWindow();
    static int         getWidth();
    static int         getHeight();

    static void setShouldClose(bool flag);
    static bool isShouldClose();

private:
    Window() = delete;
    ~Window() = delete;
};