#include "Application.hpp"

namespace Panthera
{
    Application::Application(ApplicationInfo &info)
    {
        m_Info.Args = CommandLineArgs(info.Args.argc, info.Args.argv);
        m_Info.Name = info.Name;
        m_Info.Version = info.Version;
        m_Info.Width = info.Width;
        m_Info.Height = info.Height;
    }

    Application *Application::Create(ApplicationInfo &info)
    {
        return new Application(info);
    }

    void Application::Run()
    {

    }
}