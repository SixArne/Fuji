module;

#include <iostream>
#include <format>
#include <string_view>
#include <memory>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/fmt/ostr.h>

export module Logger;


namespace Debug
{
    enum LogType
    {
        Trace,
        Debug,
        Warn,
        Error,
        Critical
    };

    export class Log
    {
    public:
        static void Init();
        static std::shared_ptr<spdlog::logger>& GetLogger();

        template<typename... Args>
        static void Debug(std::string_view format, Args&&... args);

        template<typename... Args>
        static void Trace(std::string_view format, Args&&... args);

        template<typename... Args>
        static void Warn(std::string_view format, Args&&... args);

        template<typename... Args>
        static void Error(std::string_view format, Args&&... args);

        template<typename... Args>
        static void Critical(std::string_view format, Args&&... args);

    private:
        static void LogMessage(const std::string& message, LogType type);

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

    std::shared_ptr<spdlog::logger>& Log::GetLogger()
    {
        return s_Logger;
    }

    export template<typename... Args>
    void Log::Trace(std::string_view format, Args&&... args)
    {
        const std::string& result = std::vformat(format, std::make_format_args(args...));
        LogMessage(result, LogType::Trace);
    }

    export template<typename... Args>
    void Log::Debug(std::string_view format, Args&&... args)
    {
        const std::string& result = std::vformat(format, std::make_format_args(args...));
        LogMessage(result, LogType::Debug);
    }

    export template<typename... Args>
    void Log::Warn(std::string_view format, Args&&... args)
    {
        const std::string& result = std::vformat(format, std::make_format_args(args...));
        LogMessage(result, LogType::Warn);
    }

    export template<typename... Args>
    void Log::Error(std::string_view format, Args&&... args)
    {
        const std::string& result = std::vformat(format, std::make_format_args(args...));
        LogMessage(result, LogType::Error);
    }

    export template<typename... Args>
    void Log::Critical(std::string_view format, Args &&... args)
    {
        const std::string& result = std::vformat(format, std::make_format_args(args...));
        LogMessage(result, LogType::Critical);
    }

    void Log::LogMessage(const std::string& message, LogType type)
    {
        auto logger = Log::GetLogger();

        switch (type)
        {
            case LogType::Trace:
                logger->trace(message);
                break;
            case LogType::Debug:
                logger->debug(message);
                break;
            case LogType::Error:
                logger->error(message);
                break;
            case LogType::Warn:
                logger->warn(message);
                break;
            case LogType::Critical:
                logger->critical(message);
                break;
        }
    }
}

/*
export template<typename... Args>
void LogMessage(std::string_view format, Args&&... args)
{
    const std::string& result = std::vformat(format, std::make_format_args(args...));
    Debug::Log::GetLogger()->trace(result);
}

void ExtraStep(const std::string& message)
{
    Debug::Log::GetLogger()->trace(message);
}

export template<typename... Args>
void LogMessageWithStep(std::string_view format, Args&&... args)
{
    const std::string& result = std::vformat(format, std::make_format_args(args...));
    ExtraStep(result);
}
*/
