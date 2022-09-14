#ifndef PANTHERA_VERSION_HPP
#define PANTHERA_VERSION_HPP

#include "ppch.hpp"

namespace Panthera
{
    struct Version
    {
        uint32_t Major = 0;
        uint32_t Minor = 3;
        uint32_t Patch = 0;

        String ToString() const
        {
            return String::From(Major) + "." + String::From(Minor) + "." + String::From(Patch);
        }

        Version(uint32_t major, uint32_t minor, uint32_t patch)
            : Major(major), Minor(minor), Patch(patch)
        {
        }
    };
}

#endif //PANTHERA_VERSION_HPP
