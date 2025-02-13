#pragma once
#include <array>
#include <queue>
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "../../utils/utils.hpp"



class Event {
private:
    static glm::vec2                           mouse_position;
    static glm::vec2                           mouse_position_frame;
    static glm::vec2                           mouse_scroll_frame;

    // Mouse Button
    static std::array<bool, MOUSE_BUTTON_SIZE> mouse_button;
    static std::array<bool, MOUSE_BUTTON_SIZE> mouse_button_frame;
    static std::queue<int>                     mouse_button_stack;

    // Keyboard Button
    static std::array<bool, KEY_BUTTON_SIZE>   key_button;
    static std::array<bool, KEY_BUTTON_SIZE>   key_button_frame;
    static std::queue<int>                     key_button_stack;

    static bool                                f_mouse_lock;
 
public:
    static bool Init(GLFWwindow* window);
    static void Terminate();

    static void poll();

    class Mouse {
    public:
        static glm::vec2 getPosition();
        static glm::vec2 getPositionDelta();
        static glm::vec2 getScroll();

        static bool isPress(int button);
        static bool isRelease(int button);
        static bool isRepeat(int button);

        static void setLock(bool flag);
        static bool isLocked();

    private:
        Mouse() = delete;
        ~Mouse() = delete;
    };

    class Keyboard {
    public:
        static bool isPress(int key);
        static bool isRelease(int key);
        static bool isRepeat(int key);

    private:
        Keyboard() = delete;
        ~Keyboard() = delete;
    };

private:
    Event() = delete;
    ~Event() = delete;

    static void setEventFunctions(GLFWwindow* window);
};