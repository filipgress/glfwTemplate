#ifndef APP_EVENT_H_
#define APP_EVENT_H_

#include "event.h"

namespace cg_window {

	class WindowCloseEvent : public Event {
		public:
			WindowCloseEvent() = default;

			EVENT_CLASS_TYPE(kWindowClose);
			EVENT_CLASS_CATEGORY(kEventCategoryApplication);
	};

	class WindowResizeEvent : public Event {
		public:
			WindowResizeEvent(uint16_t width, uint16_t height):
				width_ {width}, height_ {height} {}

			EVENT_CLASS_TYPE(kWindowResize);
			EVENT_CLASS_CATEGORY(kEventCategoryApplication);

			std::string ToString() const override { 
				std::ostringstream ss;
				ss << GetEventName() << ": " << width_ << " " << height_;
				return ss.str();
			}

			uint16_t GetWidth() const { return width_; }
			uint16_t GetHeight() const { return height_; }

		private:
			uint16_t width_;
			uint16_t height_;
	};
}

#endif // APP_EVENT_H_
