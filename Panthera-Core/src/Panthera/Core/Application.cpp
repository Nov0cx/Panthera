#include "Application.hpp"

namespace Panthera {

    void Application::SetInstance(Application *instance)
    {
        Application::s_Instance = instance;
    }

    Application* Application::GetInstance()
    {
        return Application::s_Instance;
    }

    Application::Application()
    {

    }

    Application::~Application()
    {

    }

    void Application::Run()
    {

    }
}