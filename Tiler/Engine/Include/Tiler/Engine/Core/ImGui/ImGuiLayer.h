#pragma once

#include "Tiler/Engine/Core/Layer.h"

namespace tiler {

	class ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer() override;

		void onAttach() override;
		void onDetach() override;

		void onEvent(const Event& event) override{};
		void onRender(float timestep) override;

		void onRenderBegin();
		void onRenderEnd();

	private:
		float m_time = 0.0f;
	};
}  // namespace tiler