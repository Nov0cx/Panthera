#ifndef PANTHERA_RENDERER2D_HPP
#define PANTHERA_RENDERER2D_HPP

#include "ppch.hpp"

namespace Panthera
{
    // fwd
    struct Renderer2DStorage;

    class Renderer2D
    {
    public:
        void Init();
        void Shutdown();

        void DrawIndexed();
    private:
        Renderer2DStorage* m_Storage;
    };
}

#endif //PANTHERA_RENDERER2D_HPP
