#pragma once

#include <vector>

// Forward Declaration
namespace Tiler {
	class Layer;
	class Event;
}

namespace Tiler {

	class LayerStack {
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		void RenderLayers();
		void OnEvent(const Event& event);

	private:
		std::vector<Layer*> m_Layers;
		unsigned int m_LayerInsertIndex;
	};
}

