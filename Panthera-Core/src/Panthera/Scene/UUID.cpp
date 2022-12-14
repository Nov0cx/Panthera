#include "UUID.hpp"

#include "Panthera/Utils/Random.hpp"

namespace Panthera
{
    UUID::UUID()
    {
        m_UUID = Random::RandomU64();
    }

    uint64_t UUID::Get()
    {
        return m_UUID;
    }

    UUID::UUID(uint64_t uuid)
    {
        m_UUID = uuid;
    }
}