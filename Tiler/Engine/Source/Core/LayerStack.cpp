#include "Tiler/Engine/Core/LayerStack.h"

#include "Tiler/Engine/Core/Layer.h"

namespace tiler {

	LayerStack::LayerStack() {
		m_layerInsertIndex = 0;
	}

	LayerStack::~LayerStack() {
		for (Layer* layer : m_layers) {
			delete layer;
		}
	}

	void LayerStack::pushLayer(Layer* layer) {
		m_layers.emplace(m_layers.begin() + m_layerInsertIndex, layer);
		m_layerInsertIndex++;
	}

	void LayerStack::pushOverlay(Layer* overlay) {
		m_layers.emplace_back(overlay);
	}

	void LayerStack::popLayer(Layer* layer) {
		auto it = std::find(m_layers.begin(), m_layers.end(), layer);
		if (it != m_layers.begin() + m_layerInsertIndex) {
			m_layers.erase(it);
			m_layerInsertIndex--;
		}
	}

	void LayerStack::popOverlay(Layer* overlay) {
		auto it = std::find(m_layers.begin(), m_layers.end(), overlay);
		if (it != m_layers.end()) {
			m_layers.erase(it);
		}
	}

	void LayerStack::renderLayers(float timestep) {
		for (Layer* layer : m_layers) {
			layer->onRender(timestep);
		}
	}

	void LayerStack::onEvent(const Event& event) {
		for (auto it = m_layers.rbegin(); it != m_layers.rend(); ++it) {
			const auto layer = (*it);
			layer->onEvent(event);
			if (layer->getEventHandled()) {
				break;
			}
		}
	}

}  // namespace tiler