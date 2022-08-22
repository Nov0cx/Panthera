#include "OpenGLRenderContext.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <any>
#include "Panthera/Core/Log.hpp"

namespace Panthera
{
    static bool s_GladInitialized = false;

    OpenGLRenderContext::OpenGLRenderContext(std::any nativeWindow)
    {
        m_NativeWindow = std::any_cast<GLFWwindow*>(nativeWindow);
    }

    OpenGLRenderContext::~OpenGLRenderContext()
    {}

    void OpenGLRenderContext::MakeContext()
    {
        glfwMakeContextCurrent(m_NativeWindow);

        if (!s_GladInitialized)
        {
            if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
            {
                glfwTerminate();
                ASSERT(false, "Failed to initialize GLAD!");
            }
            s_GladInitialized = true;
            if (GLAD_GL_VERSION_4_6)
            {
                LOG_DEBUG("OpenGL 4.6 is supported!")
            }
            else
            {
                ASSERT(false, "OpenGL 4.6 is not supported!")
            }

            LOG_DEBUG("OpenGL Version: {}", (char *) glGetString(GL_VERSION));
        }
    }

    void OpenGLRenderContext::SwapBuffers()
    {
        glfwSwapBuffers(m_NativeWindow);
    }
}