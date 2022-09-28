#ifndef PANTHERA_RENDERCONTEXT_HPP
#define PANTHERA_RENDERCONTEXT_HPP

#include "ppch.hpp"
#include <glm/glm.hpp>

namespace Panthera
{
    class PT_API RenderContext
    {
    public:
        static Ref<RenderContext> Create(void* nativeWindow);
    public:
        virtual void Init() = 0;
        virtual void MakeCurrent() = 0;
        virtual void SwapBuffers() = 0;
        virtual void Clear(const glm::vec4& color) = 0;
    };
}

#endif //PANTHERA_RENDERCONTEXT_HPP
