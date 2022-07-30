#include "OpenGLRenderContext.hpp"

#include <GLFW/glfw3.h>
#include <any>

namespace Panthera
{
    OpenGLRenderContext::OpenGLRenderContext(std::any nativeWindow)
    {
        m_NativeWindow = std::any_cast<GLFWwindow*>(nativeWindow);
    }

    OpenGLRenderContext::~OpenGLRenderContext()
    {}

    void OpenGLRenderContext::MakeContext()
    {
        glfwMakeContextCurrent(m_NativeWindow);
    }

    void OpenGLRenderContext::SwapBuffers()
    {
        glfwSwapBuffers(m_NativeWindow);
    }
}