#ifndef PANTHERA_RENDERER_HPP
#define PANTHERA_RENDERER_HPP

#include "ppch.hpp"

#include "Window/Window.hpp"

namespace Panthera
{
    enum class PT_API RenderAPI
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

    class PT_API GlobalRenderer
    {
    public:
        static void Init(WindowInfo info);
        static void Shutdown();
        static bool RequestShutdown();
        static bool ShutdownAllowed();

        static void BeginFrame();
        static void EndFrame();

        static void SetRenderAPI(RenderAPI api);
        static RenderAPI GetAPI();

        static void SubmitFunc(const std::function<void()>& func);
        static void SubmitFunc(std::function<void()>& func);

        static Ref<Window> GetMainWindow();
        static void SetMainWindow(Ref<Window> window);
        static Ref<Window> CreateAndGetWindow(const WindowInfo &info);
    private:

    };
}

#endif //PANTHERA_RENDERER_HPP
