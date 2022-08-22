#ifndef PANTHERA_RENDERCONTEXT_HPP
#define PANTHERA_RENDERCONTEXT_HPP

#include "Panthera/Core/Pointer.hpp"
#include <any>
#include "Panthera/Window/Window.hpp"

namespace Panthera
{
    class RenderContext
    {
    public:
        static Ref<RenderContext> Create(std::any nativeWindow);

        virtual void MakeContext() = 0;
        virtual void SwapBuffers() = 0;
    };
}

#endif //PANTHERA_RENDERCONTEXT_HPP
