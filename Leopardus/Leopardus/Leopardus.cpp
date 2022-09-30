#include "Panthera/Panthera.hpp"

#include "Panthera/Core/Entry.hpp"

namespace Panthera
{
    class Leopardus : public Layer
    {
    public:
        Leopardus() : Layer()
        {
        }

        void OnEnable() override
        {
            m_Renderer.Init();
        }

        void OnDisable() override
        {
            m_Renderer.Shutdown();
        }

        void OnUpdate(Timestep ts) override
        {
            GlobalRenderer::SubmitFunc([]() mutable {
                RenderCommand::Clear({0.2f, 0.2f, 0.2f, 1.0f});
            });
            GlobalRenderer::SubmitFunc([this]() mutable {
                //m_Renderer.DrawTriangle({-0.5f, -0.2f}, {0.f, 0.5f}, {0.5f, -0.2f}, {1.f, 0.f, 0.f, 1.f});
                m_Renderer.DrawQuad({0.f, 0.f}, {1.f, 1.f}, {0.f, 1.f, 0.f, 1.f});
                m_Renderer.Flush();
            });
        }

    private:
        Renderer2D m_Renderer;
    };

    void ApplicationCreationCallback(ApplicationInfo *outInfo)
    {
        outInfo->Name = "Leopardus";
        outInfo->Version = {0, 3, 0};
        outInfo->Width = 500;
        outInfo->Height = 500;
    }

    int Main(Application *app)
    {
        app->PushLayer(new Leopardus());
        app->Run();

        return 0;
    }
}