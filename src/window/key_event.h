#ifndef KEY_EVENT_H_
#define KEY_EVENT_H_

#include "event.h"

namespace cg_window {

	// TODO:
	// - implement KeyEventTyped for glfwSetCharCallback()
	
	class KeyEvent : public Event {
		public:
			uint16_t GetKeyCode() const { return key_code_; }

			EVENT_CLASS_CATEGORY((kEventCategoryInput | kEventCategoryKeyboard));

		protected:
			
			// Should be used as interface for other key events
			KeyEvent(uint16_t key_code):
				key_code_ {key_code} {}

			uint16_t key_code_;
	};

	class KeyPressEvent : public KeyEvent {
		public:
			KeyPressEvent(uint16_t key_code, uint16_t repeat_count):
				KeyEvent {key_code}, repeat_count_ {repeat_count} {}

			EVENT_CLASS_TYPE(kKeyPress);

			std::string ToString() const override {
				std::ostringstream ss;
				ss << GetEventName() << ": " << key_code_ << 
					"[" << repeat_count_ << " repeats]";

				return ss.str();
			}

			uint16_t GetRepeatCount() const { return repeat_count_; }

		private:
			uint16_t repeat_count_;
	};

	class KeyReleaseEvent : public KeyEvent {
		public:
			KeyReleaseEvent(uint16_t key_code):
				KeyEvent {key_code} {}

			EVENT_CLASS_TYPE(kKeyRelease);

			std::string ToString() const override {
				std::ostringstream ss;
				ss << GetEventName() << ": " << key_code_;

				return ss.str();
			}
	};
}

#endif // KEY_EVENT_H_
