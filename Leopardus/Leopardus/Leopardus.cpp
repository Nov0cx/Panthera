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
            m_Texture = Texture2D::LoadFromDisk(AssetLoader::GetAssetPath("Panthera/assets/demo_textures/ball.jpeg"));
            FramebufferInfo info;
            info.Width = 1280;
            info.Height = 720;
            info.ColorAttachments = { { Texture2DFormat::RGBA, 1 } };

            m_Framebuffer = Framebuffer::Create(info);
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
                //m_Framebuffer->Bind();
                m_Renderer.DrawQuad({0.f, 0.f}, {1.f, 1.f}, {1.f, 1.f, 1.f, 1.f}, m_Texture);
                m_Renderer.Flush();
                //m_Framebuffer->Unbind();
            });
        }

    private:
        Renderer2D m_Renderer;
        Ref<Texture2D> m_Texture;
        Ref<Framebuffer> m_Framebuffer;
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