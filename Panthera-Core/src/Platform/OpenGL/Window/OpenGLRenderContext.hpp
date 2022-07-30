#ifndef PANTHERA_OPENGLRENDERCONTEXT_HPP
#define PANTHERA_OPENGLRENDERCONTEXT_HPP

#include "Panthera/Window/RenderContext.hpp"
#include "Panthera/Window/Window.hpp"
#include "Panthera/Core/Pointer.hpp"

// fwd
typedef struct GLFWwindow GLFWwindow;

namespace Panthera
{
    class OpenGLRenderContext : public RenderContext
    {
    public:
        OpenGLRenderContext(std::any nativeWindow);
        ~OpenGLRenderContext();

        void MakeContext() override;
        void SwapBuffers() override;

    private:
        GLFWwindow* m_NativeWindow;
    };
}

#endif //PANTHERA_OPENGLRENDERCONTEXT_HPP
