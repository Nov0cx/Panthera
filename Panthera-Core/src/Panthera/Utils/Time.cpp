#include "Time.hpp"

#include <chrono>

namespace Panthera::Time
{

    float GetSeconds()
    {
        auto now = std::chrono::high_resolution_clock::now();
        return std::chrono::time_point_cast<std::chrono::milliseconds>(now).time_since_epoch().count() * 0.001f;
    }

    float GetMilliseconds()
    {
        auto now = std::chrono::high_resolution_clock::now();
        return std::chrono::time_point_cast<std::chrono::microseconds>(now).time_since_epoch().count() * 0.001f;
    }

    float GetMinutes()
    {
        auto now = std::chrono::high_resolution_clock::now();
        return std::chrono::time_point_cast<std::chrono::seconds>(now).time_since_epoch().count() * 0.0166666667f;
    }
}