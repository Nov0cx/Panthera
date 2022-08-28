#ifndef PANTHERA_PROJECTSERIALIZER_HPP
#define PANTHERA_PROJECTSERIALIZER_HPP

#include "Project.hpp"

namespace Panthera
{
    class ProjectSerializer
    {
    public:
        static void Serialize(Project* project);
        static Project* Deserialize(const std::string& path);
    };
}

#endif //PANTHERA_PROJECTSERIALIZER_HPP
