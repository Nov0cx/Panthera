#ifndef PANTHERA_RENDERER2D_HPP
#define PANTHERA_RENDERER2D_HPP

#include "ppch.hpp"

namespace Panthera
{
    // fwd
    struct Renderer2DStorage;

    class PT_API Renderer2D
    {
    public:
        void Init();
        void Shutdown();

        void DrawTriangle(const glm::vec2 &p1, const glm::vec2 &p2, const glm::vec2 &p3);

        void DrawIndexed(uint32_t count);
        void Flush();
    private:
        Renderer2DStorage* m_Storage;
    };
}

#endif //PANTHERA_RENDERER2D_HPP
