#pragma once

#include "Event.h"


namespace Tiler {

	EventDispatcher& EventDispatcher::getInstance() {
		// Note: This function if NOT thread-safe. To make it thread-safe
		// use lock_guard, double-checked locking or atomic operations.
		static EventDispatcher instance;
		return instance;
	}

	void EventDispatcher::Subscribe(EventType eventType, const EventCallback& callback) {
		eventCallbacks[eventType].push_back(callback);
	}

	void EventDispatcher::Unsubscribe(EventType eventType, const EventCallback& callback) {
		auto& callbacks{ eventCallbacks[eventType] };
		callbacks.erase(
			std::remove_if(callbacks.begin(), callbacks.end(), [&callback](const EventCallback& cb) {
				return cb.target_type() == callback.target_type() && cb.target<void(const Event&)>() == callback.target<void(const Event&)>();
				}),
			callbacks.end()
		);
	}

	void EventDispatcher::Dispatch(const Event& event) {
		auto& callbacks{ eventCallbacks[event.GetEventType()] };
		for (const auto& callback : callbacks) {
			callback(event);
		}
		callbacks.clear();
	}

	EventDispatcher::EventDispatcher() = default;
	EventDispatcher::~EventDispatcher() = default;

} // namespace Tiler
