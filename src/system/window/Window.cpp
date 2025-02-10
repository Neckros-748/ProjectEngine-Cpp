#include "Window.h"

#include "../../system/console/Console.h"

GLFWwindow* Window::window = nullptr;
int         Window::width  = 0;
int         Window::height = 0;



////////////////////////////////////////////////////////////////////////////////
/////   WINDOW                                                             /////
////////////////////////////////////////////////////////////////////////////////

bool Window::Init(int width, int height, const std::string& title)
{
    // Инициализация GLFW
    if (!glfwInit()) {
        Console::error("Window system (Init)", { "Error initializing window control system. Error initializing GLFM library." });
        return false;
    }
    else {
        glfwSetErrorCallback([](int error, const char* description) {
            Console::error("Error initializing window control system.", { description });
            });
        Console::info("Window system (Init)", { "Initializing the window control system. Initialization of GLFM library completed successfully." });
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

    // Создание окна
    Window::window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!Window::window) {
        glfwTerminate();
        Console::error("Window system (Init)", { "Error initializing window control system. Error creating application window." });
        return false;
    }
    else {
        Console::info("Window system (Init)", { "Initializing the window control system. Creation of the application window completed successfully." });
    }

    glfwMakeContextCurrent(Window::window);

    // Инициализация GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwDestroyWindow(window);
        glfwTerminate();
        Console::error("Window system (Init)", { "Error initializing window control system. Error initializing GLAD library." });
        return false;
    }
    else {
        Console::info("Window system (Init)", { "Initializing the window control system. Initialization of GLAD library completed successfully." });
    }

    Console::info("Window system (Init)", {
        "Initialization of the window control system completed successfully. Display information about the OpenGL version and renderer.",
        std::string("OpenGL version: ") + reinterpret_cast<const char*>(glGetString(GL_VERSION)),
        std::string("Renderer:       ") + reinterpret_cast<const char*>(glGetString(GL_RENDERER)),
        });

    glViewport(0, 0, width, height);
    Window::width  = width;
    Window::height = height;

    return true;
}

void Window::Terminate()
{
    if (window) {
        glfwDestroyWindow(window);
        window = nullptr;
    }
    glfwTerminate();
    Console::info("Window system (Terminate)", { "Terminating the window control system completed successfully." });
}

void Window::swapBuffer()
{
    glfwSwapBuffers(Window::window);
}

void Window::clear()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::setShouldClose(bool flag)
{
    glfwSetWindowShouldClose(Window::window, flag);
}

bool Window::isShouldClose()
{
    return Window::window ? glfwWindowShouldClose(Window::window) : true;
}

int Window::getWidth()
{
    return Window::width;
}

int Window::getHeight()
{
    return Window::height;
}