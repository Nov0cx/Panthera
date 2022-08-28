#ifndef PANTHERA_PROJECTSERIALIZER_HPP
#define PANTHERA_PROJECTSERIALIZER_HPP

#include "Project.hpp"
#include "Panthera/Core/Pointer.hpp"

namespace Panthera
{
    class ProjectSerializer
    {
    public:
        static void Serialize(Ref<Project> project);
        static Ref<Project> Deserialize(const std::string& path);
    };
}

#endif //PANTHERA_PROJECTSERIALIZER_HPP
