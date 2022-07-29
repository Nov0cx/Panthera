#include "Application.hpp"

namespace Panthera
{

    Application *Application::s_Instance;

    void Application::SetInstance(void *instance)
    {
        Application::s_Instance = reinterpret_cast<Application *>(instance);
    }

    Application *Application::GetInstance()
    {
        return Application::s_Instance;
    }

    Application::Application()
    {
        SetInstance(this);
        Init();
    }

    Application::~Application()
    {
        for (auto& layer : m_LayerStack.m_Layers)
        {
            layer->SetActive(false);
        }
    }

    void Application::Init()
    {

    }

    void Application::Run()
    {
        while (m_Running)
        {
            m_LayerStack.OnUpdate()

            /*
            m_LayerStack.OnImGuiUpdate()
             */
        }
    }


}