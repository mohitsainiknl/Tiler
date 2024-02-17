#include "Tiler/Engine/Core/Application.h"

#include "Tiler/Engine/Base.h"


namespace Tiler {

	void Application::Run() {

		TL_CORE_INFO("Hello Tiler Engine!");
		TL_CORE_ASSERT(true, "This Assertion Never Fails!");

#ifdef TL_ENABLE_ASSERTS
		TL_CORE_INFO("Assertion Enabled!");
#endif

#ifdef TL_ENABLE_INTERNAL_LOGS
		TL_CORE_INFO("Internal Logs Enabled!");
#endif

	}
}
