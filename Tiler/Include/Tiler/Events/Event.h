#pragma once

#include <fmt/format.h>

#include <vector>
#include <string>
#include <functional>
#include <unordered_map>


#define BIT(x) (1 << x)

namespace Tiler {

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

		MOUSE_BUTTON_PRESSED,
		MOUSE_BUTTON_RELEASED,
		MOUSE_MOVED,
		MOUSE_SCROLLED
	};

	enum EventCategory {
		NONE = 0,
		EVENT_CATEGORY_KEYBOARD      = BIT(0),
		EVENT_CATEGORY_MOUSE_BUTTON  = BIT(1),
		EVENT_CATEGORY_MOUSE         = BIT(2),
		EVENT_CATEGORY_INPUT         = BIT(3),
		EVENT_CATEGORY_APPLICATION   = BIT(4),

		MAX_BIT_POSITION = 4
	};

	class Event {
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); };

		inline bool IsInCategory(EventCategory category) const {
			return GetCategoryFlags() & category;
		}

		virtual ~Event() = default;
	protected:
		Event() = default;
	};

#define EVENT_CLASS_TYPE(type) \
	static EventType GetStaticType() { return EventType::##type; } \
	virtual EventType GetEventType() const override { return GetStaticType(); } \
	virtual const char* GetName() const override { return #type; }
								
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }


	using EventCallback = std::function<void(const Event&)>;

	class EventDispatcher {
	public:
		EventDispatcher();
		~EventDispatcher();

		bool Subscribe(EventType eventType, const EventCallback& callback);
		bool Subscribe(EventCategory eventCategory, const EventCallback& callback);

		bool SubscribeOnce(EventType eventType, const EventCallback& callback);
		bool SubscribeOnce(EventCategory eventCategory, const EventCallback& callback);

		bool Unsubscribe(EventType eventType, const EventCallback& callback);
		bool Unsubscribe(EventCategory eventCategory, const EventCallback& callback);

		bool Dispatch(const Event& event);

	private:
		bool Subscribe(std::vector<EventCallback>& callbacks, const EventCallback& callback);
		bool Unsubscribe(std::vector<EventCallback>& callbacks, const EventCallback& callback);

		std::unordered_map<EventType, std::vector<EventCallback>> m_EventCallbacksByType;
		std::unordered_map<EventCategory, std::vector<EventCallback>> m_EventCallbacksByCategory;
	};

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
