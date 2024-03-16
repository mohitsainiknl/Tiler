
#include "Tiler/Engine/Core/Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace tiler {

	std::shared_ptr<spdlog::logger> Log::m_loggerCore;
	std::shared_ptr<spdlog::logger> Log::m_loggerUser;

	void Log::initialize() {
		spdlog::set_pattern("%^[%T] %n: %v%$");

		m_loggerCore = spdlog::stdout_color_mt("TILER");
		m_loggerUser = spdlog::stdout_color_mt("APP");

		m_loggerCore->set_level(spdlog::level::trace);
		m_loggerUser->set_level(spdlog::level::trace);
	}

}  // namespace tiler
