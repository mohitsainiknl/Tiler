#include "Tiler/Engine/Core/Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"


namespace Tiler {

	std::shared_ptr<spdlog::logger> Log::s_LoggerCore;
	std::shared_ptr<spdlog::logger> Log::s_LoggerUser;

	void Log::Initialize() {
		spdlog::set_pattern("%^[%T] %n: %v%$");

		s_LoggerCore = spdlog::stdout_color_mt("TILER");
		s_LoggerUser = spdlog::stdout_color_mt("APP");

		s_LoggerCore->set_level(spdlog::level::trace);
		s_LoggerUser->set_level(spdlog::level::trace);
	}

}
