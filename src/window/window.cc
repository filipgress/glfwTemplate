#include "window.h"

#include "app_event.h"
#include "key_event.h"
#include "mouse_event.h"

namespace cg_window {
	Window::Window(WindowProps props): props_ {props} {
		if (!glfwInit())
			throw std::runtime_error(MSG("Unable to initialize GLFW library"));

		// glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);		// disable window resizing
		
		window_ = glfwCreateWindow(props_.width, props_.height, 
															 props_.title.c_str(), nullptr, nullptr);

		if (!window_) {
			glfwTerminate();
			throw std::runtime_error(MSG("Unable to initialize GLFW library"));
		}

		glfwSetErrorCallback(GLFWErrorCallback);

		// To be able to access window data from glfw callbacks
		glfwSetWindowUserPointer(window_, &props_);
		glfwMakeContextCurrent(window_);

		glfwSetWindowCloseCallback(window_,
				[](GLFWwindow* window) {
			WindowProps* data = static_cast<WindowProps* >(glfwGetWindowUserPointer(window));

			WindowCloseEvent event;
			data->event_cb(event);
		});

		glfwSetWindowSizeCallback(window_,
				[](GLFWwindow* window, int width, int height) { 
			WindowProps* data = static_cast<WindowProps* >(glfwGetWindowUserPointer(window));

			data->width = width;
			data->height = height;

			WindowResizeEvent event(width, height);
			data->event_cb(event);
		});

		glfwSetKeyCallback(window_, 
				[](GLFWwindow* window, int key, int scan_code, int action, int mods) { 
			WindowProps* data = static_cast<WindowProps* >(glfwGetWindowUserPointer(window));
			(void)scan_code, (void)mods; // not using as of now

			switch (action) {
				case GLFW_PRESS: {
					KeyPressEvent event(key, 0);
					data->event_cb(event);
					break;
				}
				case GLFW_REPEAT: {
					KeyPressEvent event(key, 1);
					data->event_cb(event);
					break;
				}
				case GLFW_RELEASE: {
					KeyReleaseEvent event(key);
					data->event_cb(event);
					break;
				}
			}
		});

		glfwSetMouseButtonCallback(window_,
				[](GLFWwindow* window, int button, int action, int mods) {
			WindowProps* data = static_cast<WindowProps* >(glfwGetWindowUserPointer(window));
			(void)mods;
			
			switch (action) {
				case GLFW_PRESS: {
					MousePressEvent event(static_cast<MouseCode>(button));
					data->event_cb(event);
					break;
				}
				case GLFW_RELEASE: {
					MouseReleaseEvent event(static_cast<MouseCode>(button));
					data->event_cb(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(window_,
				[](GLFWwindow* window, double x_offset, double y_offset) {
			WindowProps* data = static_cast<WindowProps* >(glfwGetWindowUserPointer(window));

			MouseScrollEvent event(x_offset, y_offset);
			data->event_cb(event);
		});

		glfwSetCursorPosCallback(window_,
				[](GLFWwindow* window, double x_pos, double y_pos) {
			WindowProps* data = static_cast<WindowProps* >(glfwGetWindowUserPointer(window));

			MouseMoveEvent event(x_pos, y_pos);
			data->event_cb(event);
		});
	}

	Window::~Window() {
		glfwTerminate();
	}

	void Window::GLFWErrorCallback(int error_code, const char* description) {
		throw std::runtime_error(MSG("GLFW error [", error_code, "]: ", description));
	}
}
