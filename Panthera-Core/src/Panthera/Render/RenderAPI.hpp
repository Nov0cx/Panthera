#ifndef PANTHERA_RENDERAPI_HPP
#define PANTHERA_RENDERAPI_HPP

#include <cinttypes>

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

    using RendererID = std::uint32_t;
}

#endif //PANTHERA_RENDERAPI_HPP
