#include "Random.hpp"

namespace Panthera::Random
{

    static std::random_device s_RandomDevice;
    static std::mt19937_64 s_Engine(s_RandomDevice());

    uint64_t U64(uint64_t min, uint64_t max)
    {
        return std::uniform_int_distribution<uint64_t>{min, max}(s_Engine);
    }

    uint32_t U32(uint32_t min, uint32_t max)
    {
        return std::uniform_int_distribution<uint32_t>{min, max}(s_Engine);
    }

    uint16_t U16(uint16_t min, uint16_t max)
    {
        return std::uniform_int_distribution<uint16_t>{min, max}(s_Engine);
    }

    uint8_t U8(uint8_t min, uint8_t max)
    {
        return std::uniform_int_distribution<uint16_t>{min, max}(s_Engine);
    }

    int64_t I64(int64_t min, int64_t max)
    {
        return std::uniform_int_distribution<int64_t>{min, max}(s_Engine);
    }

    int32_t I32(int32_t min, int32_t max)
    {
        return std::uniform_int_distribution<int32_t>{min, max}(s_Engine);
    }

    int16_t I16(int16_t min, int16_t max)
    {
        return std::uniform_int_distribution<int16_t>{min, max}(s_Engine);
    }

    int8_t I8(int8_t min, int8_t max)
    {
        return std::uniform_int_distribution<int16_t>{min, max}(s_Engine);
    }

    float F32(float min, float max)
    {
        return std::uniform_real_distribution<float>{min, max}(s_Engine);
    }

    double F64(double min, double max)
    {
        return std::uniform_real_distribution<double>{min, max}(s_Engine);
    }

    bool Bool()
    {
        return U8(0, 1);
    }
}