#pragma once

#include "Tiler/Engine/Core/Events/Event.h"

namespace tiler {

	class ImGuiOverlay {
	public:
		ImGuiOverlay()  = default;
		~ImGuiOverlay() = default;

		static void init();
		static void shutdown();

		static void onEvent(const Event& event){};

		static void onRenderBegin();
		static void onRenderEnd();
	};
}  // namespace tiler