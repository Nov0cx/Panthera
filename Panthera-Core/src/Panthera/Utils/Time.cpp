#include "Time.hpp"

#include <chrono>

namespace Panthera::Time
{

    Time<std::chrono::seconds> GetSeconds()
    {
        auto now = std::chrono::high_resolution_clock::now();
        return std::chrono::time_point_cast<std::chrono::seconds>(now);
    }

    Time<std::chrono::milliseconds> GetMilliseconds()
    {
        auto now = std::chrono::high_resolution_clock::now();
        return std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    }

    Time<std::chrono::minutes> GetMinutes()
    {
        auto now = std::chrono::high_resolution_clock::now();
        return std::chrono::time_point_cast<std::chrono::minutes>(now);
    }
}