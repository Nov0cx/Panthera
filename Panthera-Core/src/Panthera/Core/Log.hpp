#ifndef PANTHERA_LOG_HPP
#define PANTHERA_LOG_HPP

#pragma warning(push, 0)

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#pragma warning(pop)

#include <memory>

namespace Panthera
{
    class Log
    {
    public:
        enum class Level
        {
            Trace,
            Debug,
            Info,
            Warn,
            Error,
            Critical
        };
    public:
        static void Init();

        template<typename... Args>
        static constexpr void LogMessage(Level level, Args&&... args);
    private:
        static std::shared_ptr<spdlog::logger> s_Logger;
    };


}

#ifdef PANTHERA_DEBUG
#define LOG_DEBUG(...) ::Panthera::Log::LogMessage(::Panthera::Log::Level::Debug, fmt::format("{}", __VA_ARGS__));
#else
#define LOG_DEBUG(...)
#endif
#ifndef PANTHERA_RELEASE
#define LOG_TRACE(...) ::Panthera::Log::LogMessage(::Panthera::Log::Level::Trace, fmt::format("{}", __VA_ARGS__));
#define LOG_INFO(...) ::Panthera::Log::LogMessage(::Panthera::Log::Level::Info, fmt::format("{}", __VA_ARGS__));
#define LOG_WARN(...) ::Panthera::Log::LogMessage(::Panthera::Log::Level::Warn, fmt::format("{}", __VA_ARGS__));
#define LOG_ERROR(...) ::Panthera::Log::LogMessage(::Panthera::Log::Level::Error, fmt::format("{}", __VA_ARGS__));

#define _LOG_CRITICAL(...) ::Panthera::Log::LogMessage(::Panthera::Log::Level::Critical,  fmt::format("{}", __VA_ARGS__));
#define ASSERT(condition, ...) \
        if (!(condition))         \
        {                       \
            _LOG_CRITICAL("Assert failed at line {} in file {}.", __LINE__, __FILE__); \
            _LOG_CRITICAL(__VA_ARGS__);\
            exit(-1);                        \
        }
#else
#define LOG_TRACE(...) ;
#define LOG_INFO(...) ;
#define LOG_WARN(...) ;
#define LOG_ERROR(...) ;
#define ASSERT(condition, ...) condition;
#endif

namespace Panthera
{
    template<typename... Args>
    constexpr void Log::LogMessage(Level level, Args&&... args)
    {
        switch (level)
        {
            case Level::Trace:
                s_Logger->trace(std::forward<Args>(args)...);
                break;
            case Level::Debug:
                s_Logger->debug(std::forward<Args>(args)...);
                break;
            case Level::Info:
                s_Logger->info(std::forward<Args>(args)...);
                break;
            case Level::Warn:
                s_Logger->warn(std::forward<Args>(args)...);
                break;
            case Level::Error:
                s_Logger->error(std::forward<Args>(args)...);
                break;
            case Level::Critical:
                s_Logger->critical(std::forward<Args>(args)...);
                break;
        }
    }
}

#endif