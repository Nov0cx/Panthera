#include "UUID.hpp"

#include "Panthera/Utils/Random.hpp"

namespace Panthera
{

    UUID::UUID()
    {
        a = Random::U16();
        b = Random::U16();
        c = Random::U16();
        d = Random::U16();
    }

    UUID::UUID(const UUID &other)
    {
        a = other.a;
        b = other.b;
        c = other.c;
        d = other.d;
    }

    UUID::UUID(const String &uuid)
    {
        String uuid2 = uuid;
        uuid2.RemoveAll(" ");
        uuid2.RemoveAll("-");
        uuid2.RemoveAll("{");
        uuid2.RemoveAll("}");

        uint64_t uuid3 = std::stoull(uuid2);

        a = (uuid3 >> 48) & 0xFFFF;
        b = (uuid3 >> 32) & 0xFFFF;
        c = (uuid3 >> 16) & 0xFFFF;
        d = (uuid3 >> 0) & 0xFFFF;
    }

    UUID::UUID(uint64_t uuid)
    {
        a = (uuid >> 48) & 0xFFFF;
        b = (uuid >> 32) & 0xFFFF;
        c = (uuid >> 16) & 0xFFFF;
        d = uuid & 0xFFFF;
    }

    UUID::UUID(uint32_t upper, uint32_t lower)
    {
        a = (upper >> 16) & 0xFFFF;
        b = upper & 0xFFFF;
        c = (lower >> 16) & 0xFFFF;
        d = lower & 0xFFFF;
    }

    UUID::UUID(uint16_t a, uint16_t b, uint16_t c, uint16_t d)
    {
        this->a = a;
        this->b = b;
        this->c = c;
        this->d = d;
    }

    bool UUID::operator==(const UUID &other) const
    {
        return a == other.a && b == other.b && c == other.c && d == other.d;
    }

    bool UUID::operator!=(const UUID &other) const
    {
        return !(*this == other);
    }

    bool UUID::operator==(const String &other) const
    {
        return ToString() == other;
    }

    bool UUID::operator!=(const String &other) const
    {
        return !(*this == other);
    }

    bool UUID::operator==(uint64_t other) const
    {
        return GetUUID() == other;
    }

    uint64_t UUID::GetUUID() const
    {
        return ((uint64_t)a << 48) | ((uint64_t)b << 32) | ((uint64_t)c << 16) | d;
    }

    String UUID::ToString() const
    {
        return String::From(GetUUID());
    }

    UUID::operator uint64_t() const
    {
        return GetUUID();
    }

    UUID::operator String() const
    {
        return ToString();
    }
}