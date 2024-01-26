#pragma once

#include <functional>
#include <vector>
#include <string>
#include <sstream>
#include <fmt/format.h>


#define BIT(x) (1 << x)

namespace Tiler {

	enum class EventType {
		NONE = 0,
		KEY_PRESSED,
		KEY_RELEASED,
	};

	enum EventCategory {
		NONE = 0,
		EVENT_CATEGORY_KEYBOARD      = BIT(0),
		EVENT_CATEGORY_MOUSE_BUTTON  = BIT(1),
		EVENT_CATEGORY_MOUSE         = BIT(2),
		EVENT_CATEGORY_INPUT         = BIT(3),
		EVENT_CATEGORY_APPLICATION   = BIT(4),
	};

	class Event {
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual unsigned short GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); };

		inline bool IsInCategory(EventCategory category) const {
			return GetCategoryFlags() & category;
		}
	};

#define EVENT_CLASS_TYPE(type) \
	static EventType GetStaticType() { return EventType::##type; } \
	virtual EventType GetEventType() const override { return GetStaticType(); } \
	virtual const char* GetName() const override { return #type; }
								
#define EVENT_CLASS_CATEGORY(category) virtual unsigned short GetCategoryFlags() const override { return category; }


	using EventCallback = std::function<void(const Event&)>;

	class EventDispatcher {
	public:
		// Create the only instance of this object and return a pointer to it
		static EventDispatcher& getInstance();

		bool Subscribe(EventType eventType, const EventCallback& callback);
		bool Subscribe(EventCategory eventCategory, const EventCallback& callback);
		bool Unsubscribe(EventType eventType, const EventCallback& callback);
		bool Unsubscribe(EventCategory eventCategory, const EventCallback& callback);
		bool Dispatch(const Event& event);

	private:
		bool Subscribe(std::vector<EventCallback>& callbacks, const EventCallback& callback);
		bool Unsubscribe(std::vector<EventCallback>& callbacks, const EventCallback& callback);

		std::unordered_map<EventType, std::vector<EventCallback>> m_EventCallbacksByType;
		std::unordered_map<EventCategory, std::vector<EventCallback>> m_EventCallbacksByCategory;

		//Making them NOT accessible
		EventDispatcher();
		~EventDispatcher();
		EventDispatcher(const EventDispatcher&) = delete;
		EventDispatcher& operator=(const EventDispatcher&) = delete;
	};

	// Help to print `Event` on ostream, Example - std::cout << e << std::endl;
	inline std::ostream& operator<<(std::ostream& os, const Event& event) {
		return os << event.ToString();
	}

} // namespace Tiler

// Help to print `Event` directly in logger, Example - TL_INFO(event)
// And, should be implemented for Event and Event derived classes.
#define FMT_SPECIALIZATION(type) \
    template <> \
    struct fmt::formatter<type> { \
        constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); } \
        \
        template <typename FormatContext> \
        auto format(const type& obj, FormatContext& ctx) { \
            return fmt::format_to(ctx.out(), "{}", obj.ToString()); \
        } \
    }

FMT_SPECIALIZATION(Tiler::Event);
