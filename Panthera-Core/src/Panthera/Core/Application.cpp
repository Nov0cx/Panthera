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
        while (p_Running)
        {

            float now = Time::GetSeconds();
            float delta = now - m_LastFrameTime;
            m_LastFrameTime = now;
            m_Timestep = delta;

            p_Running = !m_Window->ShouldBeClosed();

            if (!m_Minimized)
                m_LayerStack.OnUpdate(m_Timestep);

            /*
            m_LayerStack.OnImGuiUpdate()
             */
            if (!m_Minimized)
                m_Window->OnUpdate();
        }
    }

    void Application::CallEvent(Event &event)
    {
        static Event::Listener<WindowResizeEvent> resizeListener([this](auto  &&PH1) { OnResize(std::forward<decltype(PH1)>(PH1)); });
        resizeListener.Run(event, EventSubType::WindowResizeEvent);

        m_LayerStack.OnEvent(event);
    }

    void Application::OnResize(WindowResizeEvent &event)
    {
        if (event.Width == 0 || event.Height == 0)
        {
            m_Minimized = true;
            return;
        }

        m_Minimized = false;
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