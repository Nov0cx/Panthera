#include "Log.hpp"

#pragma warning(push, 0)

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#pragma warning(pop)


#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Panthera
{
    static Ref <spdlog::logger> s_Logger;

    void Log::Init()
    {
        auto colorRef = CreateRef<spdlog::sinks::stdout_color_sink_mt>();
        colorRef->set_pattern("%^[%T] [%l] %n: %v%$");

        s_Logger = CreateRef<spdlog::logger>("PANTHERA", spdlog::sinks_init_list{
                colorRef,
                CreateRef<spdlog::sinks::basic_file_sink_mt>("PANTHERA.log", true)});

        spdlog::register_logger(s_Logger);

        s_Logger->set_level(spdlog::level::trace);
        s_Logger->flush_on(spdlog::level::trace);
    }

    template<class... Args>
    Log::Log(Log::LogLevel level, Args... args)
    {
        switch (level)
        {
            case LogLevel::Trace:
                s_Logger->trace("{0}", fmt::format(args...));
                break;
            case LogLevel::Debug:
                s_Logger->debug("{0}", fmt::format(args...));
                break;
            case LogLevel::Info:
                s_Logger->info("{0}", fmt::format(args...));
                break;
            case LogLevel::Warn:
                s_Logger->warn("{0}", fmt::format(args...));
                break;
            case LogLevel::Error:
                s_Logger->error("{0}", fmt::format(args...));
                break;
            case LogLevel::Critical:
                s_Logger->critical("{0}", fmt::format(args...));
                break;
        }
    }
}