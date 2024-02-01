#pragma once

#include "Tiler/Layer.h"

#include "Tiler/Events/KeyEvent.h"
#include "Tiler/Events/ApplicationEvent.h"
#include "Tiler/Events/MouseEvent.h"

namespace Tiler {

	class ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer() override;

		void OnAttach() override;
		void OnDetach() override;

		void OnUpdate() override;
		void OnEvent(const Event& event) override;

	private:
		void OnMouseButtonPressedEvent(MouseButtonPressedEvent& event);
		void OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event);
		void OnMouseMovedEvent(MouseMovedEvent& event);
		void OnMouseScrolledEvent(MouseScrolledEvent& event);
		void OnKeyPressedEvent(KeyPressedEvent& event);
		void OnKeyReleasedEvent(KeyReleasedEvent& event);
		void OnKeyTypedEvent(KeyTypedEvent& event);
		void OnWindowResizeEvent(WindowResizeEvent& event);

	private:
		float m_Time = 0.0f;
	};
}