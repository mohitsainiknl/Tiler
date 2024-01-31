#include "Tiler/Layer.h"


namespace Tiler {

	Layer::~Layer() {

	}

	Layer::Layer(const std::string& debugName) : m_DebugName(debugName) {
		m_EventHandled = false;
	}


}