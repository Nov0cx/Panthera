#ifndef PANTHERA_LOG_HPP
#define PANTHERA_LOG_HPP

#pragma warning(push, 0)

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#pragma warning(pop)

#include <memory>

#include <Vendor/debugbreak/debugbreak.hpp>

namespace Panthera
{
    class Log
    {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; }
    private:
        static std::shared_ptr<spdlog::logger> s_Logger;
    };
}


#ifdef PANTHERA_DEBUG

#define PT_LOG_DEBUG(...) ::Panthera::Log::GetLogger()->debug(__VA_ARGS__);
#define PT_LOG_TRACE(...) ::Panthera::Log::GetLogger()->trace(__VA_ARGS__);
#define PT_LOG_INFO(...) ::Panthera::Log::GetLogger()->info(__VA_ARGS__);
#define PT_LOG_WARNING(...) ::Panthera::Log::GetLogger()->warn(__VA_ARGS__);
#define PT_LOG_ERROR(...) ::Panthera::Log::GetLogger()->error(__VA_ARGS__);
#define PT_LOG_FATAL(...) ::Panthera::Log::GetLogger()->critical(__VA_ARGS__);

#define PT_ASSERT(condition, ...) if (!(condition)) { PT_LOG_FATAL(__VA_ARGS__); debug_break(); }

#else

#define PT_LOG_DEBUG(...)
#define PT_LOG_TRACE(...)
#define PT_LOG_INFO(...)
#define PT_LOG_WARNING(...)
#define PT_LOG_ERROR(...)
#define PT_LOG_FATAL(...)

#define PT_ASSERT(condition, ...)

#endif

#define PT_ASSERT_HANDLE(condition, handle) if (!(condition)) { handle(); }

#endif //PANTHERA_LOG_HPP
