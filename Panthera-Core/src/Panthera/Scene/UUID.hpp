#ifndef PANTHERA_UUID_HPP
#define PANTHERA_UUID_HPP

#include <cinttypes>
#include <functional>

namespace Panthera
{
    struct UUID
    {
    public:
        UUID();
        UUID(uint64_t uuid);

        uint64_t Get();

        inline operator uint64_t() const
        {
            return m_UUID;
        }

        inline bool operator==(const UUID& other) const
        {
            return m_UUID == other.m_UUID;
        }
    private:
        uint64_t m_UUID;
    };
}

namespace std
{
    //template <typename T> struct hash;

    template<>
    struct hash<Panthera::UUID>
    {
        size_t operator()(const Panthera::UUID &uuid) const
        {
            return hash<uint64_t>()(uuid);
        }
    };
}


#endif //PANTHERA_UUID_HPP
