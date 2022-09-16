#include "Panthera/Panthera.hpp"
#include "Panthera/RenderCore.hpp"

#include "Panthera/Core/Entry.hpp"

namespace Panthera
{
    void ApplicationCreationCallback(ApplicationInfo *outInfo)
    {
        outInfo->Name = "Leopardus";
        outInfo->Version = {0, 3, 0};
        outInfo->Width = 500;
        outInfo->Height = 500;
    }

    int Main(Application *app)
    {
        WindowInfo windowInfo;
        windowInfo.Title = app->GetInfo().Name + " - " + app->GetInfo().Version.ToString();
        windowInfo.Width = app->GetInfo().Width;
        windowInfo.Height = app->GetInfo().Height;
        windowInfo.VSync = false;

        GlobalRenderer::Init(windowInfo);

        while (!GlobalRenderer::ShutdownAllowed())
        {
            GlobalRenderer::BeginFrame();
            GlobalRenderer::SubmitFunc([]() {
                GlobalRenderer::GetMainWindow()->GetRenderContext()->Clear({0.2f, 0.2f, 0.2f, 1.0f});
            });
            GlobalRenderer::SubmitFunc([]() {
                GlobalRenderer::GetMainWindow()->Update();
            });
            GlobalRenderer::EndFrame();
        }

        GlobalRenderer::Shutdown();

        return 0;
    }
}