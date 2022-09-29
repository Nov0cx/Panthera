#ifndef PANTHERA_OPENGLRENDERCONTEXT_HPP
#define PANTHERA_OPENGLRENDERCONTEXT_HPP

#include "ppch.hpp"
#include "Panthera/Renderer/Context/RenderContext.hpp"
#include "Panthera/Renderer/Window/Window.hpp"

namespace Panthera
{
    class OpenGLRenderContext : public RenderContext
    {
    public:
        OpenGLRenderContext(void* nativeWindow);
        virtual void Init() override;
        virtual void MakeCurrent() override;
        virtual void SwapBuffers() override;
        virtual void Clear(const glm::vec4& color) override;
    private:
        void* m_Window;
    };
}

#endif //PANTHERA_OPENGLRENDERCONTEXT_HPP
