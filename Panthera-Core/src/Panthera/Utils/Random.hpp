#ifndef PANTHERA_RANDOM_HPP
#define PANTHERA_RANDOM_HPP

#include <cinttypes>

namespace Panthera::Random
{
    uint64_t RandomU64();
    uint32_t RandomU32();
    uint16_t RandomU16();
    float RandomFloat();
    double RandomDouble();
    bool RandomBool();
}

#endif //PANTHERA_RANDOM_HPP
