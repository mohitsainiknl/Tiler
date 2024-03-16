#pragma once

#include <fmt/format.h>

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

#define BIT(x) (1 << x)

namespace tiler {

	enum class EventType {
		NONE = 0,

		WINDOW_CLOSE,
		WINDOW_RESIZE,
		WINDOW_FOCUS,
		WINDOW_FOCUS_LOST,
		WINDOW_MOVED,

		APP_TICK,
		APP_UPDATE,
		APP_RENDER,

		KEY_PRESSED,
		KEY_RELEASED,
		KEY_TYPED,

		MOUSE_BUTTON_PRESSED,
		MOUSE_BUTTON_RELEASED,
		MOUSE_MOVED,
		MOUSE_SCROLLED
	};

	enum EventCategory {
		NONE                        = 0,
		EVENT_CATEGORY_KEYBOARD     = BIT(0),
		EVENT_CATEGORY_MOUSE_BUTTON = BIT(1),
		EVENT_CATEGORY_MOUSE        = BIT(2),
		EVENT_CATEGORY_INPUT        = BIT(3),
		EVENT_CATEGORY_APPLICATION  = BIT(4),

		MAX_BIT_POSITION = 4
	};

	class Event {
	public:
		virtual EventType getEventType() const = 0;
		virtual const char* getName() const    = 0;
		virtual int getCategoryFlags() const   = 0;
		virtual std::string toString() const { return getName(); };

		inline bool isInCategory(EventCategory category) const { return getCategoryFlags() & category; }

		virtual ~Event() = default;

	protected:
		Event() = default;
	};

#define EVENT_CLASS_TYPE(type)                                                                                         \
	static EventType getStaticType() {                                                                                 \
		return EventType::##type;                                                                                      \
	}                                                                                                                  \
	virtual EventType getEventType() const override {                                                                  \
		return getStaticType();                                                                                        \
	}                                                                                                                  \
	virtual const char* getName() const override {                                                                     \
		return #type;                                                                                                  \
	}

#define EVENT_CLASS_CATEGORY(category)                                                                                 \
	virtual int getCategoryFlags() const override {                                                                    \
		return category;                                                                                               \
	}

	using EventCallback = std::function<void(const Event&)>;

	class EventDispatcher {
	public:
		EventDispatcher();
		~EventDispatcher();

		bool subscribe(const EventCallback& callback);
		bool subscribe(EventType eventType, const EventCallback& callback);
		bool subscribe(EventCategory eventCategory, const EventCallback& callback);

		bool subscribeOnce(EventType eventType, const EventCallback& callback);
		bool subscribeOnce(EventCategory eventCategory, const EventCallback& callback);

		bool unsubscribe(const EventCallback& callback);
		bool unsubscribe(EventType eventType, const EventCallback& callback);
		bool unsubscribe(EventCategory eventCategory, const EventCallback& callback);

		bool dispatch(const Event& event);

	private:
		bool subscribe(std::vector<EventCallback>& callbacks, const EventCallback& callback);
		bool unsubscribe(std::vector<EventCallback>& callbacks, const EventCallback& callback);

		std::vector<EventCallback> m_eventCallbacks;
		std::unordered_map<EventType, std::vector<EventCallback>> m_eventCallbacksByType;
		std::unordered_map<EventCategory, std::vector<EventCallback>> m_eventCallbacksByCategory;
	};

}  // namespace tiler

// Help to print `Event` directly in logger, Example - TL_INFO(event)
// And, should be implemented for Event and Event derived classes.
#define FMT_SPECIALIZATION(type)                                                                                       \
	template<> struct fmt::formatter<type> {                                                                           \
		constexpr auto parse(format_parse_context& ctx) {                                                              \
			return ctx.begin();                                                                                        \
		}                                                                                                              \
                                                                                                                       \
		template<typename FormatContext> auto format(const type& obj, FormatContext& ctx) {                            \
			return fmt::format_to(ctx.out(), "{}", obj.toString());                                                    \
		}                                                                                                              \
	}

FMT_SPECIALIZATION(tiler::Event);
