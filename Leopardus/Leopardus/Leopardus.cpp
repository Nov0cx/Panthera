#include "Panthera/Panthera.hpp"

#include "Panthera/Core/Entry.hpp"
#include "Panthera/UI/UIWindow.hpp"

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
            WindowInfo wInfo;
            wInfo.Width = 1280;
            wInfo.Height = 720;
            wInfo.Title = "Leopardus2";
            m_Window = GlobalRenderer::CreateAndGetWindow(wInfo);
            m_Window->Init();

            GlobalRenderer::GetMainWindow()->GetRenderContext()->MakeCurrent();

            m_Renderer.Init();
            m_Texture = Texture2D::LoadFromDisk(AssetLoader::GetAssetPath("Panthera/assets/demo_textures/ball.jpeg"));

            FramebufferInfo info;
            info.Width = 700;
            info.Height = 500;
            info.ColorAttachments = { { Texture2DFormat::RGBA, 1 } };

            m_Framebuffer = Framebuffer::Create(info);

            float apr = 700.f / 500.f;
            m_Camera = OrthographicCamera(-apr, apr, -1, 1);

            m_Window->GetRenderContext()->MakeCurrent();
            m_Renderer2.Init();
        }

        void OnDisable() override
        {
            m_Renderer.Shutdown();
        }

        void OnUpdate(Timestep ts) override
        {
            UI::BeginContext("Hey");
            UI::EndContext();

            GlobalRenderer::SubmitFunc([this]() mutable {
                m_Framebuffer->Bind();

                GlobalRenderer::GetMainWindow()->GetRenderContext()->Clear({0.2f, 0.2f, 0.2f, 1.0f});
                m_Renderer.Begin(m_Camera);
                m_Renderer.DrawTriangle({-0.5f, -0.2f}, {0.f, 0.5f}, {0.5f, -0.2f}, {1.f, 0.f, 0.f, 1.f});
                m_Renderer.DrawQuad({0.f, 0.f}, {1.f, 1.f}, {1.f, 1.f, 1.f, 0.6f}, m_Texture);
                m_Renderer.End();
                m_Framebuffer->Unbind();

                // Draw framebuffer
                m_Renderer.Begin(m_Camera);
                m_Renderer.DrawFramebuffer(m_Framebuffer, GlobalRenderer::GetMainWindow());

                m_Window->GetRenderContext()->MakeCurrent();
                m_Renderer2.Begin(m_Camera);
                m_Window->GetRenderContext()->Clear({0.2f, 0.2f, 0.2f, 1.0f});
                m_Renderer2.DrawQuad({0.f, 0.f}, {1.f, 1.f}, {1.f, 1.f, 1.f, 0.6f});
                m_Renderer2.End();


                m_Framebuffer->GetColorAttachment(0)->Clear(0);

            });
        }

    private:
        Renderer2D m_Renderer;
        Renderer2D m_Renderer2;
        Ref<Texture2D> m_Texture;
        Ref<Framebuffer> m_Framebuffer;
        Ref<Window> m_Window;
        OrthographicCamera m_Camera;
    };

    void ApplicationCreationCallback(ApplicationInfo *outInfo)
    {
        outInfo->Name = "Leopardus";
        outInfo->Version = {0, 3, 0};
        outInfo->Width = 700;
        outInfo->Height = 500;
    }

    int Main(Application *app)
    {
        app->PushLayer(new Leopardus());
        app->Run();

        return 0;
    }
}