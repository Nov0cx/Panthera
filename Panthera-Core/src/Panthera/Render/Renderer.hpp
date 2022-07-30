#ifndef PANTHERA_RENDERER_HPP
#define PANTHERA_RENDERER_HPP

namespace Panthera
{
    // Want to support all of them.
    enum class RendererAPI
    {
        NONE = 0,
        OpenGL = 1,
        Vulkan = 2,
        Direct3D = 3,
        Metal = 4,
        OpenGLES = 5,
    };

    class Renderer
    {
    public:
        static RendererAPI GetAPI();
        static void SetAPI(RendererAPI api);
    private:
        Renderer() = default;
    };
}

#endif //PANTHERA_RENDERER_HPP
