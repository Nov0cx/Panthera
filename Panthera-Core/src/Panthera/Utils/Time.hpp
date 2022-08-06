#ifndef PANTHERA_TIME_HPP
#define PANTHERA_TIME_HPP

#include <chrono>

namespace Panthera::Time
{
    template<typename T>
    using Time = std::chrono::time_point<std::chrono::high_resolution_clock, T>;
    using Duration = std::chrono::duration<float>;

    Time<std::chrono::seconds> GetSeconds();
    Time<std::chrono::milliseconds> GetMilliseconds();
    Time<std::chrono::minutes> GetMinutes();
}

#endif //PANTHERA_TIME_HPP
