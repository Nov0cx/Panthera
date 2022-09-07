#ifndef PANTHERA_MISCUTILS_HPP
#define PANTHERA_MISCUTILS_HPP

#include <vector>
#include <algorithm>
#include <functional>

namespace Panthera::Utils
{
    namespace STLVector
    {
        template<typename T>
        inline void Remove(std::vector<T> &vector, const T &element)
        {
            vector.erase(std::remove(vector.begin(), vector.end(), element), vector.end());
        }

        template<typename T>
        inline bool Contains(const std::vector<T> &vector, const T &element)
        {
            return std::find(vector.begin(), vector.end(), element) != vector.end();
        }

        template<typename T, typename Callback>
        inline bool Contains(const std::vector<T> &vector, const T &element, Callback comparator)
        {
            for (const T &item : vector)
            {
                if (comparator(item, element))
                    return true;
            }
            return false;
        }
    }

}

#endif //PANTHERA_MISCUTILS_HPP
