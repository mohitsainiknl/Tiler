#pragma once

#include <spdlog/spdlog.h>
#include <memory>

namespace Tiler {
	class Log
	{
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	public:
		static void init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	};
}

// Core log macros
#define TL_CORE_TRACE(...) ::Tiler::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define TL_CORE_INFO(...)  ::Tiler::Log::GetCoreLogger()->info(__VA_ARGS__)
#define TL_CORE_WARN(...)  ::Tiler::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define TL_CORE_ERROR(...) ::Tiler::Log::GetCoreLogger()->error(__VA_ARGS__)
#define TL_CORE_FATAL(...) ::Tiler::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define TL_TRACE(...) ::Tiler::Log::GetClientLogger()->trace(__VA_ARGS__)
#define TL_INFO(...)  ::Tiler::Log::GetClientLogger()->info(__VA_ARGS__)
#define TL_WARN(...)  ::Tiler::Log::GetClientLogger()->warn(__VA_ARGS__)
#define TL_ERROR(...) ::Tiler::Log::GetClientLogger()->error(__VA_ARGS__)
#define TL_FATAL(...) ::Tiler::Log::GetClientLogger()->fatal(__VA_ARGS__)

