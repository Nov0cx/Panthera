#include "LOG.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Panthera
{

    PT_API std::shared_ptr <spdlog::logger> s_Logger;

    void Log::Init()
    {
        auto colorRef = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        colorRef->set_pattern("%^[%T] [%l] %n: %v%$");

        s_Logger = std::make_shared<spdlog::logger>("PANTHERA", spdlog::sinks_init_list{
                colorRef,
                std::make_shared<spdlog::sinks::basic_file_sink_mt>("PANTHERA.log", true)});

        spdlog::register_logger(s_Logger);

        s_Logger->set_level(spdlog::level::trace);
        s_Logger->flush_on(spdlog::level::trace);
    }
}
