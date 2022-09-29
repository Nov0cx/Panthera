#ifndef PANTHERA_PAIR_HPP
#define PANTHERA_PAIR_HPP
#include "DLL.hpp"
namespace Panthera
{
    template<typename T, typename U>
    struct PT_API Pair
    {
        T first;
        U second;

        Pair() = default;
        Pair(const T& first, const U& second)
            : first(first), second(second) {}
    };
}

#endif //PANTHERA_PAIR_HPP
