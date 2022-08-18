#ifndef PANTHERA_LOG_HPP
#define PANTHERA_LOG_HPP

#include "Panthera/Core/Pointer.hpp"

#pragma warning(push, 0)

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#pragma warning(pop)

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
        static inline void LogMessage(Level level, fmt::format_string<Args...> format, Args&&... args)
        {
            switch (level)
            {
                case Level::Trace:
                    s_Logger->trace("{}", fmt::format(format, std::forward<Args>(args)...));
                    break;
                case Level::Debug:
                    s_Logger->debug("{}", fmt::format(format, std::forward<Args>(args)...));
                    break;
                case Level::Info:
                    s_Logger->info("{}", fmt::format(format, std::forward<Args>(args)...));
                    break;
                case Level::Warn:
                    s_Logger->warn("{}", fmt::format(format, std::forward<Args>(args)...));
                    break;
                case Level::Error:
                    s_Logger->error("{}", fmt::format(format, std::forward<Args>(args)...));
                    break;
                case Level::Critical:
                    s_Logger->critical("{}", fmt::format(format, std::forward<Args>(args)...));
                    break;
            }
        }
    private:
        static Ref<spdlog::logger> s_Logger;
    };


}

#ifdef PANTHERA_DEBUG
#define LOG_DEBUG(...) ::Panthera::Log::LogMessage(::Panthera::Log::Level::Debug, "{}", __VA_ARGS__);
#else
#define LOG_DEBUG(...)
#endif
#ifndef PANTHERA_RELEASE
#define LOG_TRACE(...) ::Panthera::Log::LogMessage(::Panthera::Log::Level::Trace, "{}", __VA_ARGS__);
#define LOG_INFO(...) ::Panthera::Log::LogMessage(::Panthera::Log::Level::Info, "{}", __VA_ARGS__);
#define LOG_WARN(...) ::Panthera::Log::LogMessage(::Panthera::Log::Level::Warn, "{}", __VA_ARGS__);
#define LOG_ERROR(...) ::Panthera::Log::LogMessage(::Panthera::Log::Level::Error, "{}", __VA_ARGS__);

#define _LOG_CRITICAL(...) ::Panthera::Log::LogMessage(::Panthera::Log::Level::Critical, "{}", __VA_ARGS__);
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
#endif