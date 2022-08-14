#ifndef PANTHERA_LOG_HPP
#define PANTHERA_LOG_HPP

#include "Panthera/Core/Pointer.hpp"


namespace Panthera
{
    class Log
    {
    public:
        enum class LogLevel
        {
            Trace,
            Debug,
            Info,
            Warn,
            Error,
            Critical,
        };

        static void Init();

        template<class... Args>
        static void LogMessage(LogLevel level, Args... args);
    };
}

#ifdef PANTHERA_DEBUG
#define LOG_DEBUG(...) ::Panthera::Log::LogMessage(::Panthera::Log::LogLevel::Debug, __VA_ARGS__)
#else
#define LOG_DEBUG(...)
#endif
#ifndef PANTHERA_RELEASE
#define LOG_TRACE(...) ::Panthera::Log::LogMessage(::Panthera::Log::LogLevel::Trace, __VA_ARGS__)
#define LOG_INFO(...) ::Panthera::Log::LogMessage(::Panthera::Log::LogLevel::Info, __VA_ARGS__)
#define LOG_WARN(...) ::Panthera::Log::LogMessage(::Panthera::Log::LogLevel::Warn, __VA_ARGS__)
#define LOG_ERROR(...) ::Panthera::Log::LogMessage(::Panthera::Log::LogLevel::Error, __VA_ARGS__)

#define _LOG_CRITICAL(...) ::Panthera::Log::LogMessage(::Panthera::Log::LogLevel::Critical, __VA_ARGS__)
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
#define ASSERT(condition, ...) condition; if (false) exit(-1);
#endif
#endif