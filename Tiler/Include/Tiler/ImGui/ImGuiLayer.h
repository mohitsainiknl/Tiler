#pragma once

#include "Tiler/Layer.h"


namespace Tiler {

	class ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer() override;

		void OnAttach() override;
		void OnDetach() override;

		void OnEvent(const Event& event) override {};
		void OnRender() override;

		void OnRenderBegin();
		void OnRenderEnd();

	private:
		float m_Time = 0.0f;
	};
}