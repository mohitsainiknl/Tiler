#pragma once

#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#pragma warning(pop)

#include <memory>

// Internal Core log macros
#ifdef TL_ENABLE_DEV_LOGS
#define TL_CORE_TRACE(...) ::tiler::Log::getLoggerCore()->trace(__VA_ARGS__)
#define TL_CORE_DEBUG(...) ::tiler::Log::getLoggerCore()->debug(__VA_ARGS__)
#else
#define TL_CORE_TRACE(...)
#define TL_CORE_DEBUG(...)
#endif

// Core log macros
#define TL_CORE_INFO(...)     ::tiler::Log::getLoggerCore()->info(__VA_ARGS__)
#define TL_CORE_WARN(...)     ::tiler::Log::getLoggerCore()->warn(__VA_ARGS__)
#define TL_CORE_ERROR(...)    ::tiler::Log::getLoggerCore()->error(__VA_ARGS__)
#define TL_CORE_CRITICAL(...) ::tiler::Log::getLoggerCore()->critical(__VA_ARGS__)

// Client log macros
#define TL_TRACE(...)    ::tiler::Log::getLoggerUser()->trace(__VA_ARGS__)
#define TL_DEBUG(...)    ::tiler::Log::getLoggerUser()->debug(__VA_ARGS__)
#define TL_INFO(...)     ::tiler::Log::getLoggerUser()->info(__VA_ARGS__)
#define TL_WARN(...)     ::tiler::Log::getLoggerUser()->warn(__VA_ARGS__)
#define TL_ERROR(...)    ::tiler::Log::getLoggerUser()->error(__VA_ARGS__)
#define TL_CRITICAL(...) ::tiler::Log::getLoggerUser()->critical(__VA_ARGS__)

namespace tiler {
	class Log {
	public:
		static void initialize();
		inline static std::shared_ptr<spdlog::logger>& getLoggerCore() { return m_loggerCore; }
		inline static std::shared_ptr<spdlog::logger>& getLoggerUser() { return m_loggerUser; }

	private:
		Log()                      = default;
		Log(const Log&)            = delete;
		Log& operator=(const Log&) = delete;

		static std::shared_ptr<spdlog::logger> m_loggerCore;
		static std::shared_ptr<spdlog::logger> m_loggerUser;
	};
}  // namespace tiler
