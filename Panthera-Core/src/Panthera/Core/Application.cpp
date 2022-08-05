#include "Application.hpp"

#include "Log.hpp"
#include <string>
#include "Panthera/Render/Shader.hpp"

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
        ASSERT(m_Runfiles != nullptr, "Failed to create runfiles: {}", error);

        std::string vertex = R""""(
#version 450
layout(location = 0) in vec4 position;
void main()
{

   gl_Position = position;

}
        )"""";

        std::string fragment = R""""(
#version 450 core
layout(location = 0) out vec4 color;
void main()
{
   color = vec4(0.2, 0.3, 0.8, 1.0);
}
        )"""";

        LOG_INFO("Vertex Shader: {}", vertex)
        LOG_INFO("Fragment Shader: {}", fragment)
        auto shader = ShaderLibrary::CreateShader("Test", vertex, fragment);
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

    std::string Application::GetAssetPath(const char *filepath)
    {
        return m_Runfiles->Rlocation(filepath);
    }


    AppProps::AppProps(ProgramArgs args, const char *name, unsigned int width, unsigned int height, bool vSync) : Args(args), Name(name),
                                                                                                Width(width),
                                                                                                Height(height),
                                                                                                VSync(vSync)
    {}

}