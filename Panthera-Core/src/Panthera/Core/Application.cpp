#include "Application.hpp"

namespace Panthera {

    Application* Application::s_Instance;

    void Application::SetInstance(void *instance)
    {
        Application::s_Instance = reinterpret_cast<Application*>(instance);
    }

    Application* Application::GetInstance()
    {
        return Application::s_Instance;
    }

    Application::Application()
    {
        SetInstance(this);
    }

    Application::~Application()
    {

    }

    void Application::Run()
    {

    }
}