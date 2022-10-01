#include "Application.hpp"

#include "Panthera/Utils/Time.hpp"
#include "Panthera/Event/EventSystem.hpp"
#include "Panthera/Event/WindowEvents.hpp"

namespace Panthera
{
    Application::Application(ApplicationInfo &info)
    {
        m_Info.Args = CommandLineArgs(info.Args.argc, info.Args.argv);
        m_Info.Name = info.Name;
        m_Info.Version = info.Version;
        m_Info.Width = info.Width;
        m_Info.Height = info.Height;

        WindowInfo windowInfo;
        windowInfo.Title = m_Info.Name + " - " + m_Info.Version.ToString();
        windowInfo.Width = m_Info.Width;
        windowInfo.Height = m_Info.Height;
        windowInfo.VSync = false;
        windowInfo.Fullscreen = false;

        EventManager::Init();
        GlobalRenderer::Init(windowInfo);

        m_LayerStack = new LayerStack();

        EventManager::RegisterListener<WindowResizeEvent>([this](WindowResizeEvent &event) mutable
                                       {
                                           if (event.Width == 0 || event.Height == 0)
                                               m_Minimized = true;
                                           else
                                               m_Minimized = false;
                                       }, EventPriority::High);
    }

    Application::~Application()
    {
        GlobalRenderer::Shutdown();
        delete m_LayerStack;
    }

    Application *Application::Create(ApplicationInfo &info)
    {
        return new Application(info);
    }

    void Application::Run()
    {
        while (!GlobalRenderer::ShutdownAllowed())
        {
            float now = Time::GetSeconds();
            float delta = now - m_LastFrameTime;
            m_LastFrameTime = now;
            Timestep ts = delta;

            GlobalRenderer::BeginFrame();

            GlobalRenderer::GetMainWindow()->GetRenderContext()->MakeCurrent();

            if (!m_Minimized)
                m_LayerStack->OnUpdate(ts);

            GlobalRenderer::SubmitFunc([]()
                                       {
                                           GlobalRenderer::GetMainWindow()->Update();
                                       });

            GlobalRenderer::EndFrame();
        }
    }
}