#ifndef PANTHERA_RENDERER_HPP
#define PANTHERA_RENDERER_HPP

#include "ppch.hpp"

namespace Panthera
{
    enum class RenderAPI
    {
        None = 0,
#ifdef PANTHERA_OPENGL
        OpenGL,
#endif
#ifdef PANTHERA_VULKAN
        Vulkan,
#endif
#ifdef PANTHERA_DIRECTX
        DirectX
#endif
    };

    class GlobalRenderer
    {
    public:
        static void Init();
        static void Shutdown();

        static void SetRenderAPI(RenderAPI api);
        static RenderAPI GetAPI();
    };
}

#endif //PANTHERA_RENDERER_HPP
