#ifndef PANTHERA_UUID_HPP
#define PANTHERA_UUID_HPP

#include "ppch.hpp"

namespace Panthera
{
    class UUID
    {
    public:
        UUID();
        UUID(const UUID &other);
        UUID(const String &uuid);
        UUID(uint64_t uuid);
        UUID(uint32_t upper, uint32_t lower);
        UUID(uint16_t a, uint16_t b, uint16_t c, uint16_t d);

        bool operator==(const UUID &other) const;
        bool operator!=(const UUID &other) const;
        bool operator==(const String &other) const;
        bool operator!=(const String &other) const;
        bool operator==(uint64_t other) const;

        uint64_t GetUUID() const;
        String ToString() const;
        operator uint64_t() const;
        operator String() const;

    private:
        uint16_t a = 0, b = 0, c = 0, d = 0;
    };
}

#endif //PANTHERA_UUID_HPP
