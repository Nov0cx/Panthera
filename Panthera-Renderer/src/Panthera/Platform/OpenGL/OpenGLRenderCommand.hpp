#ifndef PANTHERA_OPENGLRENDERCOMMAND_HPP
#define PANTHERA_OPENGLRENDERCOMMAND_HPP

#include "ppch.hpp"

namespace Panthera
{
    class OpenGLRenderCommand
    {
    public:
        static void DrawIndexed(uint32_t count);
        static void Clear(const glm::vec4 &color);
        static void EnableBlending();
    };
}

#endif //PANTHERA_OPENGLRENDERCOMMAND_HPP