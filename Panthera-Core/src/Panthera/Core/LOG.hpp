#ifndef PANTHERA_LOG_HPP
#define PANTHERA_LOG_HPP

#include <fmt/core.h>
#include <fmt/color.h>
#include <fmt/chrono.h>
#include <fmt/format.h>

#include <Vendor/debugbreak/debugbreak.hpp>

namespace Panthera
{
    class Logger
    {
    public:
        enum class Level
        {
            Trace,
            Info,
            Warning,
            Error,
            Fatal
        };

    public:
        static void Init();

        template<class... Args>
        static void Trace(fmt::format_string<Args...> format, Args&&... args)
        {
            fmt::print(fg(fmt::color::light_yellow), "[PANTHERA] [{:%Y-%m-%d %H:%M:%S}] [TRACE] {}\n", fmt::localtime(std::time(nullptr)), fmt::format(format, std::forward<Args>(args)...));
            fmt::print(fg(fmt::color::white), "");
        }

        template<class... Args>
        static void Info(fmt::format_string<Args...> format, Args&&... args)
        {
            fmt::print(fg(fmt::color::light_blue), "[PANTHERA] [{:%Y-%m-%d %H:%M:%S}] [INFO] {}\n", fmt::localtime(std::time(nullptr)), fmt::format(format, std::forward<Args>(args)...));
            fmt::print(fg(fmt::color::white), "");
        }

        template<class... Args>
        static void Warning(fmt::format_string<Args...> format, Args&&... args)
        {
            fmt::print(fg(fmt::color::fire_brick), "[PANTHERA] [{:%Y-%m-%d %H:%M:%S}] [WARNING] {}\n", fmt::localtime(std::time(nullptr)), fmt::format(format, std::forward<Args>(args)...));
            fmt::print(fg(fmt::color::white), "");
        }

        template<class... Args>
        static void Error(fmt::format_string<Args...> format, Args&&... args)
        {
            fmt::print(fg(fmt::color::magenta), "[PANTHERA] [{:%Y-%m-%d %H:%M:%S}] [ERROR] {}\n", fmt::localtime(std::time(nullptr)), fmt::format(format, std::forward<Args>(args)...));
            fmt::print(fg(fmt::color::white), "");
        }

        template<class... Args>
        static void Fatal(fmt::format_string<Args...> format, Args&&... args)
        {
            fmt::print(fg(fmt::color::red), "[PANTHERA] [{:%Y-%m-%d %H:%M:%S}] [FATAL] {}\n", fmt::localtime(std::time(nullptr)), fmt::format(format, std::forward<Args>(args)...));
            fmt::print(fg(fmt::color::white), "");
        }

        template<class... Args>
        static void Log(Level level, fmt::format_string<Args...> format, Args&&... args)
        {
            switch (level)
            {
                case Level::Trace:
                    Trace(format, std::forward<Args>(args)...);
                    break;
                case Level::Info:
                    Info(format, std::forward<Args>(args)...);
                    break;
                case Level::Warning:
                    Warning(format, std::forward<Args>(args)...);
                    break;
                case Level::Error:
                    Error(format, std::forward<Args>(args)...);
                    break;
                case Level::Fatal:
                    Fatal(format, std::forward<Args>(args)...);
                    break;
            }
        }
    };
}


#ifdef PANTHERA_DEBUG

#define PT_LOG_TRACE(...) Panthera::Logger::Log(Panthera::Logger::Level::Trace, __VA_ARGS__)
#define PT_LOG_INFO(...) Panthera::Logger::Log(Panthera::Logger::Level::Info, __VA_ARGS__)
#define PT_LOG_WARNING(...) Panthera::Logger::Log(Panthera::Logger::Level::Warning, __VA_ARGS__)
#define PT_LOG_ERROR(...) Panthera::Logger::Log(Panthera::Logger::Level::Error, __VA_ARGS__)
#define PT_LOG_FATAL(...) Panthera::Logger::Log(Panthera::Logger::Level::Fatal, __VA_ARGS__)

#define PT_ASSERT(condition, ...) if (!(condition)) { PT_LOG_FATAL(__VA_ARGS__); /*debug_break();*/ }

#else

#define PT_LOG_TRACE(...)
#define PT_LOG_INFO(...)
#define PT_LOG_WARNING(...)
#define PT_LOG_ERROR(...)
#define PT_LOG_FATAL(...)

#define PT_ASSERT(condition, ...)

#endif

#define PT_ASSERT_HANDLE(condition, handle) if (!(condition)) { handle(); }

#endif //PANTHERA_LOG_HPP
