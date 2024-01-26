#pragma once

#include "Event.h"


namespace Tiler {

	EventDispatcher& EventDispatcher::getInstance() {
		// Note: This function if NOT thread-safe. To make it thread-safe
		// use lock_guard, double-checked locking or atomic operations.
		static EventDispatcher instance;
		return instance;
	}

	bool EventDispatcher::Subscribe(EventType eventType, const EventCallback& callback) {
		auto& callbacks{ eventCallbacks[eventType] };
		const size_t beforeSize{ callbacks.size() };

		eventCallbacks[eventType].push_back(callback);

		const size_t afterSize{ callbacks.size() };
		return (beforeSize != afterSize);
	}

	bool EventDispatcher::Unsubscribe(EventType eventType, const EventCallback& callback) {
		auto& callbacks{ eventCallbacks[eventType] };
		const size_t beforeSize{ callbacks.size() };

		callbacks.erase(
			std::remove_if(callbacks.begin(), callbacks.end(), [&callback](const EventCallback& cb) {
				return cb.target_type() == callback.target_type() && cb.target<void(const Event&)>() == callback.target<void(const Event&)>();
				}),
			callbacks.end()
		);

		const size_t afterSize{ callbacks.size() };
		return (beforeSize != afterSize);
	}

	bool EventDispatcher::Dispatch(const Event& event) {
		auto& callbacks{ eventCallbacks[event.GetEventType()] };
		const size_t beforeSize{ callbacks.size() };

		if (beforeSize) {
			for (const auto& callback : callbacks) {
				callback(event);
			}
			callbacks.clear();
			return true;
		}
		return false;
	}

	EventDispatcher::EventDispatcher() = default;
	EventDispatcher::~EventDispatcher() = default;

} // namespace Tiler
