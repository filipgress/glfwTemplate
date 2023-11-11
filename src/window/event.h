#ifndef EVENT_H_
#define EVENT_H_

namespace cg_window {

	enum class EventType {
		kNone = 0,
		kWindowClose, kWindowResize,
		kKeyPress, kKeyRelease,
		kMousePress, kMouseRelease, 
		kMouseScroll, kMouseMove
	};

	enum EventCategory {
		kNone = 0,
		kEventCategoryInput				= BIT(0),
		kEventCategoryMouse				= BIT(1),
		kEventCategoryMouseButton = BIT(2),
		kEventCategoryKeyboard		= BIT(3),
		kEventCategoryApplication = BIT(4)
	};

#define EVENT_CLASS_TYPE(type)\
	static EventType GetStaticType() { return EventType::type; }\
	virtual EventType GetEventType() const override { return GetStaticType(); }\
	virtual std::string GetEventName() const override { return #type; }\

#define EVENT_CLASS_CATEGORY(category)\
	virtual int GetCategoryFlags() const override { return (category); }

	class Event {
		public:
			virtual ~Event() = default;

			virtual EventType GetEventType() const		= 0;
			virtual int GetCategoryFlags() const			= 0;
			virtual std::string GetEventName() const	= 0;
			virtual std::string ToString() const { return GetEventName(); }

			bool IsHandled() const { return handled_; }

			inline bool IsInCategory(EventCategory category) const {
				return GetCategoryFlags() & category;
			}

		protected:
			bool handled_ = false;
	};

}

#endif // EVENT_H_
