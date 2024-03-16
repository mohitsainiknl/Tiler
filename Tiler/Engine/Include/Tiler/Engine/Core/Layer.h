#pragma once

#include <string>

// Forward Declaration
namespace tiler {
	class Event;
}

namespace tiler {

	class Layer {
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void onAttach();
		virtual void onDetach();

		virtual void onEvent(const Event& event) { m_eventHandled = false; }
		virtual void onRender(float timestep) {}

		inline const std::string& getName() const { return m_debugName; }
		inline const bool getEventHandled() const { return m_eventHandled; }

	protected:
		std::string m_debugName;
		bool m_eventHandled = false;
	};
}  // namespace tiler