#include "Tiler/Engine/Core/LayerStack.h"

#include "Tiler/Engine/Core/Layer.h"

namespace Tiler {

	LayerStack::LayerStack() {
		m_LayerInsertIndex = 0;
	}

	LayerStack::~LayerStack() {
		for (Layer* layer : m_Layers) {
			delete layer;
		}
	}


	void LayerStack::PushLayer(Layer* layer) {
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
	}


	void LayerStack::PushOverlay(Layer* overlay) {
		m_Layers.emplace_back(overlay);
	}


	void LayerStack::PopLayer(Layer* layer) {
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.begin() + m_LayerInsertIndex) {
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}


	void LayerStack::PopOverlay(Layer* overlay) {
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end()) {
			m_Layers.erase(it);
		}
	}


	void LayerStack::RenderLayers(float timestep) {
		for (Layer* layer : m_Layers) {
			layer->OnRender(timestep);
		}
	}

	void LayerStack::OnEvent(const Event& event) {
		for (auto it = m_Layers.rbegin(); it != m_Layers.rend(); ++it) {
			const auto layer = (*it);
			layer->OnEvent(event);
			if (layer->GetEventHandled())
				break;
		}
	}

}