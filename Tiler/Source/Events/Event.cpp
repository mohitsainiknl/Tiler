#pragma once

#include "Event.h"


namespace Tiler {

	EventDispatcher& EventDispatcher::getInstance() {
		// Note: This function if NOT thread-safe. To make it thread-safe
		// use lock_guard, double-checked locking or atomic operations.
		static EventDispatcher instance;
		return instance;
	}



	bool EventDispatcher::Subscribe(std::vector<EventCallback>& callbacks, const EventCallback& callback) {
		const size_t beforeSize{ callbacks.size() };

		callbacks.push_back(callback);

		const size_t afterSize{ callbacks.size() };
		return (beforeSize != afterSize);
	}

	bool EventDispatcher::Subscribe(EventType eventType, const EventCallback& callback) {
		if (eventType != EventType::NONE) {
			return Subscribe( m_EventCallbacksByType[eventType], callback );
		}
		return false;
	}

	bool EventDispatcher::Subscribe(EventCategory eventCategory, const EventCallback& callback) {
		if (eventCategory != EventCategory::NONE) {
			return Subscribe(m_EventCallbacksByCategory[eventCategory], callback);
		}
		return false;
	}



	bool EventDispatcher::Unsubscribe(std::vector<EventCallback>& callbacks, const EventCallback& callback) {
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

	bool EventDispatcher::Unsubscribe(EventType eventType, const EventCallback& callback) {
		if (eventType != EventType::NONE) {
			return Unsubscribe(m_EventCallbacksByType[eventType], callback);
		}
		return false;
	}

	bool EventDispatcher::Unsubscribe(EventCategory eventCategory, const EventCallback& callback) {
		if (eventCategory != EventCategory::NONE) {
			return Unsubscribe(m_EventCallbacksByCategory[eventCategory], callback);
		}
		return false;
	}


	bool EventDispatcher::Dispatch(const Event& event) {
		bool is_success{ false };

		// For EventType Callbacks
		{
			auto& callbacks{ m_EventCallbacksByType[event.GetEventType()] };

			if (callbacks.size()) {
				for (const auto& callback : callbacks) {
					callback(event);
				}
				callbacks.clear();
				is_success = true;
			}
		}

		// For EventCategory Callbacks
		{
			const unsigned short flags = event.GetCategoryFlags();
			const int flags_end = sizeof(flags) * 8;

			for (int i = 0; i < flags_end; ++i) {
				const EventCategory category{ static_cast<EventCategory>BIT(i) };
				if (flags & BIT(i)) {
					auto& callbacks{ m_EventCallbacksByCategory[category] };
					if (callbacks.size()) {
						for (const auto& callback : callbacks) {
							callback(event);
						}
						callbacks.clear();
						is_success = true;
					}
				}
			}
		}
		return is_success;
	}

	EventDispatcher::EventDispatcher() = default;
	EventDispatcher::~EventDispatcher() = default;

} // namespace Tiler
