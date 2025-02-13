#include "Event.h"

#include "../../system/window/Window.h"
#include "../../system/console/Console.h"

glm::vec2                           Event::mouse_position       = glm::vec2(0.0f);
glm::vec2                           Event::mouse_position_frame = glm::vec2(0.0f);
glm::vec2                           Event::mouse_scroll_frame   = glm::vec2(0.0f);

std::array<bool, MOUSE_BUTTON_SIZE> Event::mouse_button         = { false };
std::array<bool, MOUSE_BUTTON_SIZE> Event::mouse_button_frame   = { false };
std::queue<int>                     Event::mouse_button_stack;

std::array<bool, KEY_BUTTON_SIZE>   Event::key_button           = { false };
std::array<bool, KEY_BUTTON_SIZE>   Event::key_button_frame     = { false };
std::queue<int>                     Event::key_button_stack;

bool                                Event::f_mouse_lock         = false;



////////////////////////////////////////////////////////////////////////////////
/////   EVENT                                                              /////
////////////////////////////////////////////////////////////////////////////////

bool Event::Init(GLFWwindow* window)
{
	glfwSetCursorPos(window, Event::mouse_position.x, Event::mouse_position.y);
	Event::setEventFunctions(window);

	Console::info("Event system (Init)", { "Initialization of the event system completed successfully." });
	return true;
}

void Event::Terminate()
{
	Console::info("Event system (Terminate)", { "Terminating the event system completed successfully." });
}

void Event::poll()
{
	while (!Event::mouse_button_stack.empty()) {
		int button = Event::mouse_button_stack.front();
		Event::mouse_button_stack.pop();
		Event::mouse_button_frame[button] = false;
	}

	while (!Event::key_button_stack.empty()) {
		int key = Event::key_button_stack.front();
		Event::key_button_stack.pop();
		Event::key_button_frame[key] = false;
	}

	Event::mouse_position_frame = glm::vec2(0.0f);
	Event::mouse_scroll_frame   = glm::vec2(0.0f);

	glfwPollEvents();
}

void Event::setEventFunctions(GLFWwindow* window)
{
	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
		glm::vec2 position = glm::vec2(xpos, ypos);
		Event::mouse_position_frame += position - Event::mouse_position;
		Event::mouse_position       = position;
		});

	glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
		Event::mouse_scroll_frame = glm::vec2(xoffset, yoffset);
		});

	glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
		if (action == GLFW_PRESS) {
			Event::mouse_button[button]       = true;
			Event::mouse_button_frame[button] = true;
			Event::mouse_button_stack.push(button);
		}
		else if (action == GLFW_RELEASE) {
			Event::mouse_button[button]       = false;
			Event::mouse_button_frame[button] = true;
			Event::mouse_button_stack.push(button);
		}
		});

	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		if (action == GLFW_PRESS) {
			Event::key_button[key]       = true;
			Event::key_button_frame[key] = true;
			Event::key_button_stack.push(key);
		}
		else if (action == GLFW_RELEASE) {
			Event::key_button[key]       = false;
			Event::key_button_frame[key] = true;
			Event::key_button_stack.push(key);
		}
		});

	glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
		Window::width  = width;
		Window::height = height;
		});
}

////////////////////////////////////////////////////////////////////////////////
/////   EVENT :: Mouse                                                     /////
////////////////////////////////////////////////////////////////////////////////

glm::vec2 Event::Mouse::getPosition()
{
	return Event::mouse_position;
}

glm::vec2 Event::Mouse::getPositionDelta()
{
	return Event::mouse_position_frame;
}

glm::vec2 Event::Mouse::getScroll()
{
	return Event::mouse_scroll_frame;
}

bool Event::Mouse::isPress(int button)
{
	if (utils::dim_1d::isInBorder(button, MOUSE_BUTTON_SIZE))
		return Event::mouse_button_frame[button] && Event::mouse_button[button];
	return false;
}

bool Event::Mouse::isRelease(int button)
{
	if (utils::dim_1d::isInBorder(button, MOUSE_BUTTON_SIZE))
		return Event::mouse_button_frame[button] && !Event::mouse_button[button];
	return false;
}

bool Event::Mouse::isRepeat(int button)
{
	if (utils::dim_1d::isInBorder(button, MOUSE_BUTTON_SIZE))
		return Event::mouse_button[button];
	return false;
}

void Event::Mouse::setLock(bool flag)
{
    glfwSetInputMode(Window::window, GLFW_CURSOR, flag ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
    Event::f_mouse_lock = flag;
}

bool Event::Mouse::isLocked()
{
	return Event::f_mouse_lock;
}

////////////////////////////////////////////////////////////////////////////////
/////   EVENT :: Keyboard                                                  /////
////////////////////////////////////////////////////////////////////////////////

bool Event::Keyboard::isPress(int key)
{
    if (utils::dim_1d::isInBorder(key, KEY_BUTTON_SIZE))
		return Event::key_button_frame[key] && Event::key_button[key];
	return false;
}

bool Event::Keyboard::isRelease(int key)
{
	if (utils::dim_1d::isInBorder(key, KEY_BUTTON_SIZE))
		return Event::key_button_frame[key] && !Event::key_button[key];
	return false;
}

bool Event::Keyboard::isRepeat(int key)
{
	if (utils::dim_1d::isInBorder(key, KEY_BUTTON_SIZE))
		return Event::key_button[key];
	return false;
}