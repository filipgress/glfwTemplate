#include <core/pch.h>

#include <window/window.h>
#include "window/event.h"

bool running_g = true;
static void EventCallback(cg_window::Event& event) {
	std::cout << event.ToString() << std::endl;

	if (event.GetEventType() == cg_window::EventType::kWindowClose)
		running_g = false;
}

int main(const int argc, const char** argv) {
	cg_window::Window window;

	window.SetEventCallback(EventCallback);

	while (running_g) {
		glfwPollEvents();
	}

	return 0;
}
