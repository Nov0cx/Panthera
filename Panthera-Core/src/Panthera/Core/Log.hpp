#ifndef PANTHERA_LOG_HPP
#define PANTHERA_LOG_HPP

// https://github.com/TheCherno/Hazel/blob/master/Hazel/src/Hazel/Core/Log.h
// This ignores all warnings raised inside External headers
#pragma warning(push, 0)

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#pragma warning(pop)


#include "Panthera/Core/Pointer.hpp"

#include <memory>

namespace Panthera
{
    class Log
    {
    public:
        static void Init();

        static Ref<spdlog::logger> &GetLogger()
        { return s_Logger; }

    private:
        static Ref <spdlog::logger> s_Logger;
    };
}


#define LOG_DEBUG(...) ::Panthera::Log::GetLogger()->debug(__VA_ARGS__);
#define LOG_TRACE(...) ::Panthera::Log::GetLogger()->trace(__VA_ARGS__);
#define LOG_INFO(...) ::Panthera::Log::GetLogger()->info(__VA_ARGS__);
#define LOG_WARN(...) ::Panthera::Log::GetLogger()->warn(__VA_ARGS__);
#define LOG_ERROR(...) ::Panthera::Log::GetLogger()->error(__VA_ARGS__);

#define _LOG_CRITICAL(...) ::Panthera::Log::GetLogger()->critical(__VA_ARGS__);
#define ASSERT(condition, ...) \
        if (!(condition))         \
        {                       \
            _LOG_CRITICAL("Assert failed at line {} in file {}.", __LINE__, __FILE__); \
            _LOG_CRITICAL(__VA_ARGS__);\
            exit(-1);                        \
        }

#endif