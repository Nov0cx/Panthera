#include "Application.hpp"

#include "Log.hpp"

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

    Application::Application(const AppProps &props)
    {
        SetInstance(this);
        Init(props);
    }

    Application::~Application()
    {
        for (auto& layer : m_LayerStack.GetStack())
        {
            layer->SetActive(false);
        }
    }

    void Application::Init(const AppProps &props)
    {
        Log::Init();
        WindowProps windowProps(
            props.Name,
            props.Width,
            props.Height,
            props.VSync
        );
        m_Window = Window::Create(windowProps);
    }

    void Application::Run()
    {
        while (m_Running)
        {
            m_Running = !m_Window->ShouldBeClosed();

            m_LayerStack.OnUpdate();

            /*
            m_LayerStack.OnImGuiUpdate()
             */
            m_Window->OnUpdate();
        }
    }

    void Application::CallEvent(Event &event)
    {
        m_LayerStack.OnEvent(event);
    }


    AppProps::AppProps(const char *name, unsigned int width, unsigned int height, bool vSync) : Name(name),
                                                                                                Width(width),
                                                                                                Height(height),
                                                                                                VSync(vSync)
    {}
}