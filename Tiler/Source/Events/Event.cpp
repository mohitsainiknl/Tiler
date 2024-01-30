#pragma once

#include "Event.h"


namespace Tiler {

	EventDispatcher::EventDispatcher() = default;
	EventDispatcher::~EventDispatcher() = default;

	bool EventDispatcher::Subscribe(std::vector<EventCallback>& callbacks, const EventCallback& callback) {
		const size_t beforeSize{ callbacks.size() };

		callbacks.push_back(callback);

		const size_t afterSize{ callbacks.size() };
		return (beforeSize != afterSize);
	}

	bool EventDispatcher::Subscribe(EventType eventType, const EventCallback& callback) {
		if (eventType != EventType::NONE) {
			return Subscribe(m_EventCallbacksByType[eventType], callback);
		}
		return false;
	}

	bool EventDispatcher::Subscribe(EventCategory eventCategory, const EventCallback& callback) {
		if (eventCategory != EventCategory::NONE) {
			return Subscribe(m_EventCallbacksByCategory[eventCategory], callback);
		}
		return false;
	}

	// TODO
	bool EventDispatcher::SubscribeOnce(EventType eventType, const EventCallback& callback) {
		return false;
	}

	// TODO
	bool EventDispatcher::SubscribeOnce(EventCategory eventCategory, const EventCallback& callback) {
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
				is_success = true;
			}
		}

		// For EventCategory Callbacks
		{
			const int flags = event.GetCategoryFlags();
			const int max_bit = EventCategory::MAX_BIT_POSITION;

			for (int i = 0; i < max_bit; ++i) {
				if (flags & BIT(i)) {
					const EventCategory category{ static_cast<EventCategory>BIT(i) };
	
					const auto& callbacks{ m_EventCallbacksByCategory[category] };
					if (callbacks.size()) {
						for (const auto& callback : callbacks) {
							callback(event);
						}
						is_success = true;
					}
				}
			}
		}
		return is_success;
	}

} // namespace Tiler
