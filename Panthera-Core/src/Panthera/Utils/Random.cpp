#include "Random.hpp"

#include <random>

namespace Panthera::Random
{
    static std::random_device s_RandomDevice;
    static std::mt19937_64 s_Engine(s_RandomDevice());

    uint64_t RandomU64()
    {
        static std::uniform_int_distribution<uint64_t> s_Distribution;
        return s_Distribution(s_Engine);
    }

    uint32_t RandomU32()
    {
        static std::uniform_int_distribution<uint32_t> s_Distribution;
        return s_Distribution(s_Engine);
    }

    uint16_t RandomU16()
    {
        static std::uniform_int_distribution<uint16_t> s_Distribution;
        return s_Distribution(s_Engine);
    }

    float RandomFloat()
    {
        static std::uniform_real_distribution<float> s_Distribution;
        return s_Distribution(s_Engine);
    }

    double RandomDouble()
    {
        static std::uniform_real_distribution<double> s_Distribution;
        return s_Distribution(s_Engine);
    }

    bool RandomBool()
    {
        static std::uniform_int_distribution<int> s_Distribution(0, 1);
        return s_Distribution(s_Engine);
    }
}