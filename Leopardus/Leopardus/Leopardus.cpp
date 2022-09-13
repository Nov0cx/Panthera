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

        PT_LOG_INFO("Hello world!");
        PT_LOG_TRACE("my string size {}, std string size {}", sizeof(Panthera::String), sizeof(std::string));
        PT_ASSERT_HANDLE(false, []() {
            PT_LOG_ERROR("ASSERT HANDLE FAILED");
        });
        PT_LOG_FATAL("FATAL");
        PT_LOG_WARNING("WARNING");
    }

    int Main(Application *app)
    {
        WindowInfo windowInfo;
        windowInfo.Title = app->GetInfo().Name + " - " + app->GetInfo().Version.ToString();
        windowInfo.Width = app->GetInfo().Width;
        windowInfo.Height = app->GetInfo().Height;
        windowInfo.VSync = false;

        GlobalRenderer::Init(windowInfo);

        while (true)
        {
            GlobalRenderer::BeginFrame();
            GlobalRenderer::SubmitFunc([]() {
                PT_LOG_INFO("Hello world!");
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