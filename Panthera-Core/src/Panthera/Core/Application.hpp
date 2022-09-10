#ifndef PANTHERA_APPLICATION_HPP
#define PANTHERA_APPLICATION_HPP

#include "ppch.hpp"

extern int pmain(int argc, char** argv);

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
        static inline Application* GetInstance() { return s_Instance; }

    public:

    private:
        Application(ApplicationInfo info);

    private:
        static Application* s_Instance;
        static Application* Create(ApplicationInfo info);
    private:
        ApplicationInfo m_Info;
        friend int ::pmain(int argc, char** argv);
    };
}

#endif //PANTHERA_APPLICATION_HPP
