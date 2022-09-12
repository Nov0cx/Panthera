#ifndef PANTHERA_APPLICATION_HPP
#define PANTHERA_APPLICATION_HPP

#include "ppch.hpp"

extern int pmain(int argc, char **argv);

namespace Panthera
{
    struct CommandLineArgs
    {
        int argc;
        char **argv;

        CommandLineArgs(int argc, char **argv)
        {
            this->argc = argc;
            this->argv = argv;
        }

        CommandLineArgs()
        {
            this->argc = 0;
            this->argv = nullptr;
        }

        char* operator[](int index)
        {
            if (index >= argc)
                return nullptr;
            return argv[index];
        }
    };

    struct ApplicationInfo
    {
        String Name = "Panthera Application";
        CommandLineArgs Args = {};
        uint32_t Width = 0, Height = 0;
    };

    class Application
    {
    public:
        static inline Application *GetInstance()
        { return s_Instance; }

    public:
        inline ApplicationInfo& GetInfo() { return m_Info; }
        inline const ApplicationInfo& GetInfo() const { return m_Info; }

    private:
        Application(ApplicationInfo info);

    private:
        static Application *s_Instance;

        static Application *Create(ApplicationInfo info);

    private:
        ApplicationInfo m_Info;

        friend int ::pmain(int argc, char **argv);
    };
}

#endif //PANTHERA_APPLICATION_HPP
