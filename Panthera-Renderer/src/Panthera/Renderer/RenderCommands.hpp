#ifndef PANTHERA_RENDERCOMMANDS_HPP
#define PANTHERA_RENDERCOMMANDS_HPP

#include "ppch.hpp"

namespace Panthera
{
    class RenderCommand
    {
    public:
        static void DrawIndexed(uint32_t count);
        static void Clear(const glm::vec4 &color);
        static void EnableBlending();
        static void SetViewport(const glm::vec4 &viewport);
    };

}

#endif //PANTHERA_RENDERCOMMANDS_HPP
