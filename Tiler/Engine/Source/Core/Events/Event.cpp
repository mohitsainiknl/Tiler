#include "Tiler/Engine/Core/Events/Event.h"

namespace tiler {

	EventDispatcher::EventDispatcher()  = default;
	EventDispatcher::~EventDispatcher() = default;

	bool EventDispatcher::subscribe(std::vector<EventCallback>& callbacks, const EventCallback& callback) {
		const size_t beforeSize{callbacks.size()};

		callbacks.push_back(callback);

		const size_t afterSize{callbacks.size()};
		return (beforeSize != afterSize);
	}

	bool EventDispatcher::subscribe(const EventCallback& callback) {
		return subscribe(m_eventCallbacks, callback);
	}

	bool EventDispatcher::subscribe(EventType eventType, const EventCallback& callback) {
		if (eventType != EventType::NONE) {
			return subscribe(m_eventCallbacksByType[eventType], callback);
		}
		return false;
	}

	bool EventDispatcher::subscribe(EventCategory eventCategory, const EventCallback& callback) {
		if (eventCategory != EventCategory::NONE) {
			return subscribe(m_eventCallbacksByCategory[eventCategory], callback);
		}
		return false;
	}

	// TODO
	bool EventDispatcher::subscribeOnce(EventType eventType, const EventCallback& callback) {
		return false;
	}

	// TODO
	bool EventDispatcher::subscribeOnce(EventCategory eventCategory, const EventCallback& callback) {
		return false;
	}

	bool EventDispatcher::unsubscribe(std::vector<EventCallback>& callbacks, const EventCallback& callback) {
		const size_t beforeSize{callbacks.size()};

		callbacks.erase(std::remove_if(callbacks.begin(), callbacks.end(),
		                    [&callback](const EventCallback& cb) {
			                    return cb.target_type() == callback.target_type() &&
			                        cb.target<void(const Event&)>() == callback.target<void(const Event&)>();
		                    }),
		    callbacks.end());

		const size_t afterSize{callbacks.size()};
		return (beforeSize != afterSize);
	}

	bool EventDispatcher::unsubscribe(const EventCallback& callback) {
		return unsubscribe(m_eventCallbacks, callback);
	}

	bool EventDispatcher::unsubscribe(EventType eventType, const EventCallback& callback) {
		if (eventType != EventType::NONE) {
			return unsubscribe(m_eventCallbacksByType[eventType], callback);
		}
		return false;
	}

	bool EventDispatcher::unsubscribe(EventCategory eventCategory, const EventCallback& callback) {
		if (eventCategory != EventCategory::NONE) {
			return unsubscribe(m_eventCallbacksByCategory[eventCategory], callback);
		}
		return false;
	}

	bool EventDispatcher::dispatch(const Event& event) {
		bool is_success{false};

		// For Event Callbacks
		{
			auto& callbacks{m_eventCallbacks};

			if (callbacks.size()) {
				for (const auto& callback : callbacks) {
					callback(event);
				}
				is_success = true;
			}
		}

		// For EventCategory Callbacks
		{
			const int flags   = event.getCategoryFlags();
			const int max_bit = EventCategory::MAX_BIT_POSITION;

			for (int i = 0; i < max_bit; ++i) {
				if (flags & BIT(i)) {
					const EventCategory category{static_cast<EventCategory> BIT(i)};

					const auto& callbacks{m_eventCallbacksByCategory[category]};
					if (callbacks.size()) {
						for (const auto& callback : callbacks) {
							callback(event);
						}
						is_success = true;
					}
				}
			}
		}

		// For EventType Callbacks
		{
			auto& callbacks{m_eventCallbacksByType[event.getEventType()]};

			if (callbacks.size()) {
				for (const auto& callback : callbacks) {
					callback(event);
				}
				is_success = true;
			}
		}

		return is_success;
	}

}  // namespace tiler
