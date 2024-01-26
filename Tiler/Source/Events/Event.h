#pragma once

#include <functional>
#include <vector>
#include <string>


namespace Tiler {

	enum class EventType {
		NONE = 0,
		KEY_PRESSED,
		KEY_RELEASED,
	};

	class Event {
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual std::string ToString() const { return GetName(); };
	};

#define EVENT_CLASS_TYPE(type) \
	static EventType GetStaticType() { return EventType::##type; } \
	virtual EventType GetEventType() const override { return GetStaticType(); } \
	virtual const char* GetName() const override { return #type; }
								

	using EventCallback = std::function<void(const Event&)>;

	class EventDispatcher {
	public:
		// Create the only instance of this object and return a pointer to it
		static EventDispatcher& getInstance();

		void Subscribe(EventType eventType, const EventCallback& callback);
		void Unsubscribe(EventType eventType, const EventCallback& callback);
		void Dispatch(const Event& event);

	private:
		std::unordered_map<EventType, std::vector<EventCallback>> eventCallbacks;

		//Making them NOT accessible
		EventDispatcher();
		~EventDispatcher();
		EventDispatcher(const EventDispatcher&) = delete;
		EventDispatcher& operator=(const EventDispatcher&) = delete;
	};

} // namespace Tiler
