#include "Application.hpp"

namespace Panthera
{
    Application::Application(ApplicationInfo info)
        : m_Info(info)
    {}

    Application *Application::Create(ApplicationInfo info)
    {
        return new Application(info);
    }

    void Application::Run()
    {

    }
}