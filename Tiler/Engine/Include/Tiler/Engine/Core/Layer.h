#pragma once

#include <string>

// Forward Declaration
namespace Tiler {
	class Event;
}

namespace Tiler {

	class Layer {
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach();
		virtual void OnDetach();

		virtual void OnEvent(const Event& event) { m_EventHandled = false; }
		virtual void OnRender(float timestep) {}

		inline const std::string& GetName() const { return m_DebugName; }
		inline const bool GetEventHandled() const { return m_EventHandled; }

	protected:
		std::string m_DebugName;
		bool m_EventHandled = false;
	};
}