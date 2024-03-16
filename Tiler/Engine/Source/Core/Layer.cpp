#include "Tiler/Engine/Core/Layer.h"

namespace tiler {

	Layer::~Layer() {
	}

	void Layer::onAttach() {
	}

	void Layer::onDetach() {
	}

	Layer::Layer(const std::string& debugName) : m_debugName(debugName) {
	}

}  // namespace tiler