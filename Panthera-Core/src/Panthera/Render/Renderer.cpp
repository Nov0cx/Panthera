#include "Renderer.hpp"

namespace Panthera
{
    struct GlobalRendererData
    {
        RenderAPI API;
    };

    static GlobalRendererData s_globalRenderData;

    void GlobalRenderer::Init()
    {
        s_globalRenderData.API = RenderAPI::None;
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
}