#pragma once

// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#pragma warning(pop)

#include <memory>


// Internal Core log macros
#ifdef TL_ENABLE_INTERNAL_LOGS
	#define TL_CORE_TRACE(...)    ::Tiler::Log::GetLoggerCore()->trace(__VA_ARGS__)
	#define TL_CORE_DEBUG(...)    ::Tiler::Log::GetLoggerCore()->debug(__VA_ARGS__)
#else
	#define TL_CORE_TRACE(...)
	#define TL_CORE_DEBUG(...)
#endif

// Core log macros
#define TL_CORE_INFO(...)     ::Tiler::Log::GetLoggerCore()->info(__VA_ARGS__)
#define TL_CORE_WARN(...)     ::Tiler::Log::GetLoggerCore()->warn(__VA_ARGS__)
#define TL_CORE_ERROR(...)    ::Tiler::Log::GetLoggerCore()->error(__VA_ARGS__)
#define TL_CORE_CRITICAL(...) ::Tiler::Log::GetLoggerCore()->critical(__VA_ARGS__)

// Client log macros
#define TL_TRACE(...)    ::Tiler::Log::GetLoggerUser()->trace(__VA_ARGS__)
#define TL_DEBUG(...)    ::Tiler::Log::GetLoggerUser()->debug(__VA_ARGS__)
#define TL_INFO(...)     ::Tiler::Log::GetLoggerUser()->info(__VA_ARGS__)
#define TL_WARN(...)     ::Tiler::Log::GetLoggerUser()->warn(__VA_ARGS__)
#define TL_ERROR(...)    ::Tiler::Log::GetLoggerUser()->error(__VA_ARGS__)
#define TL_CRITICAL(...) ::Tiler::Log::GetLoggerUser()->critical(__VA_ARGS__)


namespace Tiler {

	class Log {
	public:
		static void OnInit();
		inline static std::shared_ptr<spdlog::logger>& GetLoggerCore() { return s_LoggerCore; }
		inline static std::shared_ptr<spdlog::logger>& GetLoggerUser() { return s_LoggerUser; }

	private:
		Log() = default;
		Log(const Log&) = delete;
		Log& operator=(const Log&) = delete;

		static std::shared_ptr<spdlog::logger> s_LoggerCore;
		static std::shared_ptr<spdlog::logger> s_LoggerUser;
	};

}
