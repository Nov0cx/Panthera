#include "Application.hpp"

#include "Log.hpp"
#include <string>

/*
 *
 *
 * std::string error;
    std::unique_ptr<Runfiles> runfiles(Runfiles::Create(argv[0], &error));

    // Important:
    //   If this is a test, use Runfiles::CreateForTest(&error).
    //   Otherwise, if you don't have the value for argv[0] for whatever
    //   reason, then use Runfiles::Create(&error).

    if (runfiles == nullptr) {
        std::cerr << "Failed to create runfiles: " << error << std::endl;
    }

    std::string path = runfiles->Rlocation("Panthera/Test/Example.tx");

    std::ifstream in(path);

    if (!in.is_open())
    {
        std::cout << "Example.tx not found" << std::endl;
        return -1;
    }

    while (in.good())
    {
        std::string line;
        std::getline(in, line);
        std::cout << line << std::endl;
    }
 */

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