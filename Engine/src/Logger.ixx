module;

#include <format>
#include <string_view>
#include <memory>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

export module Logger;


export namespace Debug
{
    class Log
    {
    public:
        static void Init();


        static std::shared_ptr<spdlog::logger>& GetLogger();

    private:
        static std::shared_ptr<spdlog::logger> s_Logger;

    };

    std::shared_ptr<spdlog::logger> Log::s_Logger{nullptr};

    void Log::Init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");

        spdlog::enable_backtrace(32);
        s_Logger = spdlog::stdout_color_mt("ENGINE");
        s_Logger->set_level(spdlog::level::trace);

        s_Logger->info("Logger initialized and ready for use.");
    }

    std::shared_ptr<spdlog::logger>& Log::GetLogger() {
        return s_Logger;
    }
}

void Log(const std::string& message)
{
    Debug::Log::GetLogger()->trace(message);
}

export template<typename... Args>
void LogMessageWithHop(std::string_view format, Args&&... args)
{
    const std::string& generatedString = std::vformat(format, std::make_format_args(args...));
    Log(generatedString);
}

export template<typename... Args>
void LogMessage(std::string_view format, Args&&... args)
{
    const std::string& generatedString = std::vformat(format, std::make_format_args(args...));
    Debug::Log::GetLogger()->trace(generatedString);
}