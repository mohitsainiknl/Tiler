#pragma once

#include <vector>

// Forward Declaration
namespace tiler {
	class Layer;
	class Event;
}  // namespace tiler

namespace tiler {

	class LayerStack {
	public:
		LayerStack();
		~LayerStack();

		void pushLayer(Layer* layer);
		void pushOverlay(Layer* overlay);
		void popLayer(Layer* layer);
		void popOverlay(Layer* overlay);

		void renderLayers(float timestep);
		void onEvent(const Event& event);

	private:
		std::vector<Layer*> m_layers;
		unsigned int m_layerInsertIndex;
	};
}  // namespace tiler
