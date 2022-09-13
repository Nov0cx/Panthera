#ifndef PANTHERA_RANDOM_HPP
#define PANTHERA_RANDOM_HPP

#include "ppch.hpp"

namespace Panthera::Random
{
    uint64_t U64(uint64_t min = 0, uint64_t max = std::numeric_limits<uint64_t>::max());

    uint32_t U32(uint32_t min = 0, uint32_t max = std::numeric_limits<uint32_t>::max());

    uint16_t U16(uint16_t min = 0, uint16_t max = std::numeric_limits<uint16_t>::max());

    uint8_t U8(uint8_t min = 0, uint8_t max = std::numeric_limits<uint8_t>::max());

    int64_t I64(int64_t min = std::numeric_limits<int64_t>::min(), int64_t max = std::numeric_limits<int64_t>::max());

    int32_t I32(int32_t min = std::numeric_limits<int32_t>::min(), int32_t max = std::numeric_limits<int32_t>::max());

    int16_t I16(int16_t min = std::numeric_limits<int16_t>::min(), int16_t max = std::numeric_limits<int16_t>::max());

    int8_t I8(int8_t min = std::numeric_limits<int8_t>::min(), int8_t max = std::numeric_limits<int8_t>::max());

    float F32(float min = 0.0f, float max = std::numeric_limits<float>::max());

    double F64(double min = 0.0, double max = std::numeric_limits<double>::max());

    bool Bool();
}

#endif //PANTHERA_RANDOM_HPP
