#include "Renderer.hpp"

namespace Panthera
{
    struct GlobalRendererData
    {
        RenderAPI API;
        Ref<Window> MainWindow;
        std::vector<Ref<Window>> Windows;
        std::vector<std::function<void()>> RendererFunctions;
    };

    static GlobalRendererData s_globalRenderData;

    void GlobalRenderer::Init(WindowInfo info)
    {
        s_globalRenderData.API = RenderAPI::None;

        // create main window
        SetMainWindow(CreateWindow(info));
        GetMainWindow()->Init();
    }

    void GlobalRenderer::Shutdown()
    {
        s_globalRenderData.API = RenderAPI::None;
    }

    void GlobalRenderer::SetRenderAPI(RenderAPI api)
    {
        s_globalRenderData.API = api;
    }

    RenderAPI GlobalRenderer::GetAPI()
    {
        return s_globalRenderData.API;
    }

    void GlobalRenderer::SubmitFunc(const std::function<void()>& func)
    {
        s_globalRenderData.RendererFunctions.push_back(func);
    }

    Ref <Window> GlobalRenderer::GetMainWindow()
    {
        return s_globalRenderData.MainWindow;
    }

    void GlobalRenderer::SetMainWindow(Ref <Window> window)
    {
        s_globalRenderData.MainWindow = window;
    }

    Ref <Window> GlobalRenderer::CreateWindow(const WindowInfo &info)
    {
        Ref<Window> window = Window::Create(info);
        s_globalRenderData.Windows.push_back(window);
        return window;
    }

    void GlobalRenderer::BeginFrame()
    {

    }

    void GlobalRenderer::EndFrame()
    {
        for (auto &func : s_globalRenderData.RendererFunctions)
            func();
        s_globalRenderData.RendererFunctions.clear();
    }
}