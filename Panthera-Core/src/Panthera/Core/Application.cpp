#include "Application.hpp"

#include "Log.hpp"
#include <string>
#include "Panthera/Render/Shader/Shader.hpp"

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
        m_Args = props.Args;

        Log::Init();
        WindowProps windowProps(
            props.Name,
            props.Width,
            props.Height,
            props.VSync
        );
        m_Window = Window::Create(windowProps);

        std::string error;
        m_Runfiles = Runfiles::Create(props.Args[0], &error);
        ASSERT(m_Runfiles != nullptr, "Failed to create runfiles: {}", error)
    }

    void Application::Run()
    {
        while (m_Running)
        {
            float now = Time::GetSeconds();
            float delta = now - m_LastFrameTime;
            m_LastFrameTime = now;
            m_Timestep = delta;

            m_Running = !m_Window->ShouldBeClosed();

            m_LayerStack.OnUpdate(m_Timestep);

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

    std::string Application::GetAssetPath(const char *filepath)
    {
        return m_Runfiles->Rlocation(filepath);
    }

    LayerStack *Application::GetLayerStack()
    {
        return &m_LayerStack;
    }

    uint32_t Application::GetWindowWidth()
    {
        return m_Window->GetWidth();
    }

    uint32_t Application::GetWindowHeight()
    {
        return m_Window->GetHeight();
    }

    Ref<Window> &Application::GetWindow()
    {
        return m_Window;
    }


    AppProps::AppProps(ProgramArgs args, const char *name, unsigned int width, unsigned int height, bool vSync) : Args(args), Name(name),
                                                                                                Width(width),
                                                                                                Height(height),
                                                                                                VSync(vSync)
    {}

}