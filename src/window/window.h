#ifndef WINDOW_H_
#define WINDOW_H_

#include <core/pch.h>
#include "event.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace cg_window {
	using EventCallbackFn = std::function<void(Event&)>;

	struct WindowProps {
		std::string title;

		uint16_t width;
		uint16_t height;

		EventCallbackFn event_cb;

		WindowProps(std::string title = PROJECT_NAME, 
								uint16_t width = 640, 
								uint16_t height = 400):
			title {title}, width {width}, height {height} {};
	};

	class Window {
		public:
			Window(WindowProps props = WindowProps());
			~Window();

			Window(const Window&) = delete;
			Window& operator=(const Window&) = delete;

			void SetEventCallback(const EventCallbackFn& callback) { props_.event_cb = callback; }

		private:

			GLFWwindow* window_;
			WindowProps props_;

			static void GLFWErrorCallback(int error_code, const char* description);
	};

}

#endif // WINDOW_H_
