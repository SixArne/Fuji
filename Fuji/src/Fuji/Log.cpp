#include "fupch.h"
#include "Log.h"

std::shared_ptr<spdlog::logger> Fuji::Log::s_CoreLogger{};
std::shared_ptr<spdlog::logger> Fuji::Log::s_ClientLogger{};

void Fuji::Log::Init()
{
	spdlog::set_pattern("%^[%T] %n: %v%$");

	s_CoreLogger = spdlog::stdout_color_mt("FUJI");
	s_CoreLogger->set_level(spdlog::level::trace);

	s_ClientLogger = spdlog::stdout_color_mt("APP");
	s_ClientLogger->set_level(spdlog::level::trace);
}