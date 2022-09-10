#ifndef PANTHERA_APPLICATION_HPP
#define PANTHERA_APPLICATION_HPP

#include "ppch.hpp"

namespace Panthera
{
    struct ApplicationInfo
    {
        std::string Name = "Panthera Application";
        uint32_t Width = 0, Height = 0;
    };

    class Application
    {
    public:

    private:
        ApplicationInfo m_Info;
    };
}

#endif //PANTHERA_APPLICATION_HPP
