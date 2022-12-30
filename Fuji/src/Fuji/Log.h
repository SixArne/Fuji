#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Fuji
{
	class FUJI_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger;  }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger;  }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

/************************************************************************/
/* Core logger macros													 */
/************************************************************************/
#define F_CORE_TRACE(...)	::Fuji::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define F_CORE_INFO(...)	::Fuji::Log::GetCoreLogger()->info(__VA_ARGS__)
#define F_CORE_DEBUG(...)	::Fuji::Log::GetCoreLogger()->debug(__VA_ARGS__)
#define F_CORE_WARN(...)	::Fuji::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define F_CORE_ERROR(...)	::Fuji::Log::GetCoreLogger()->error(__VA_ARGS__)

/************************************************************************/
/* Client logger macros													 */
/************************************************************************/
#define F_TRACE(...)	::Fuji::Log::GetClientLogger()->trace(__VA_ARGS__)
#define F_INFO(...)		::Fuji::Log::GetClientLogger()->info(__VA_ARGS__)
#define F_DEBUG(...)	::Fuji::Log::GetClientLogger()->debug(__VA_ARGS__)
#define F_WARN(...)		::Fuji::Log::GetClientLogger()->warn(__VA_ARGS__)
#define F_ERROR(...)	::Fuji::Log::GetClientLogger()->error(__VA_ARGS__)