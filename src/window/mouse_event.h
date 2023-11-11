#ifndef MOUSE_EVENT_H_
#define MOUSE_EVENT_H_

#include "event.h"

namespace cg_window {

	enum MouseCode {
		kButton0 = 0,
		kButton1 = 1,
		kButton2 = 2,
		kButton3 = 3,
		kButton4 = 4,
		kButton5 = 5,
		kButton6 = 6,
		kButton7 = 7,

		kLeftButton = kButton0,
		kRightButton = kButton1,
		kMiddleButton = kButton2,
	};
	
	class MouseButtonEvent : public Event {
		public:
			EVENT_CLASS_CATEGORY(kEventCategoryInput |
					kEventCategoryMouse | kEventCategoryMouseButton);

			MouseCode GetMouseButton() const { return button_; }

			std::string ToString() const override {
				std::ostringstream ss;
				ss << GetEventName() << ": " << button_;

				return ss.str();
			}

		protected:
			MouseButtonEvent(MouseCode button):
				button_ {button} {}

			MouseCode button_;
	};

	class MousePressEvent : public MouseButtonEvent {
		public:
			MousePressEvent(MouseCode button):
				MouseButtonEvent {button} {}

		EVENT_CLASS_TYPE(kMousePress);
	};

	class MouseReleaseEvent : public MouseButtonEvent {
		public:
			MouseReleaseEvent(MouseCode button):
				MouseButtonEvent {button} {}

			EVENT_CLASS_TYPE(kMouseRelease);
	};

	class MouseScrollEvent : public Event {
		public:
			MouseScrollEvent(double x_offset, double y_offset):
				x_offset_ {x_offset}, y_offset_ {y_offset} {}

			EVENT_CLASS_TYPE(kMouseScroll);
			EVENT_CLASS_CATEGORY(kEventCategoryInput | kEventCategoryMouse);

			double GetXOffset() const { return x_offset_; }
			double GetYOffset() const { return y_offset_; }

			std::string ToString() const override {
				std::ostringstream ss;
				ss << GetEventName() << ": " << x_offset_ << ", " << y_offset_;

				return ss.str();
			}

		private:
			double x_offset_;
			double y_offset_;
	};

	class MouseMoveEvent : public Event {
		public:
			MouseMoveEvent(double x_pos, double y_pos):
				x_pos_ {x_pos}, y_pos_ {y_pos} {}

			EVENT_CLASS_TYPE(kMouseMove);
			EVENT_CLASS_CATEGORY(kEventCategoryInput | kEventCategoryMouse);

			double GetXOffset() const { return x_pos_; }
			double GetYOffset() const { return y_pos_; }

			std::string ToString() const override {
				std::ostringstream ss;
				ss << GetEventName() << ": " << x_pos_ << ", " << y_pos_;

				return ss.str();
			}

		private:
			double x_pos_;
			double y_pos_;
	};
}

#endif // MOUSE_EVENT_H_
