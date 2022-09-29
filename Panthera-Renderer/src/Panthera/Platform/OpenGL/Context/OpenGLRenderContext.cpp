#include "OpenGLRenderContext.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Panthera/Renderer/Renderer.hpp"

namespace Panthera
{

    static bool s_GladInitialized = false;

    OpenGLRenderContext::OpenGLRenderContext(void* nativeWindow)
    {
        m_Window = nativeWindow;
    }

    void OpenGLRenderContext::Init()
    {
        MakeCurrent();

        if (!s_GladInitialized)
        {
            if (!gladLoadGL((GLADloadfunc) glfwGetProcAddress))
            {
                glfwTerminate();
                PT_LOG_FATAL("Failed to initialize GLAD!");
                return;
            }
            s_GladInitialized = true;
            if (GLAD_GL_VERSION_4_6)
            {
                PT_LOG_INFO("OpenGL 4.6 is supported!");
            } else
            {
                PT_LOG_ERROR("OpenGL 4.6 is not supported!");
                return;
            }

            PT_LOG_INFO("OpenGL Version: {}", (char *) glGetString(GL_VERSION));
        }
    }

    void OpenGLRenderContext::SwapBuffers()
    {
        glfwSwapBuffers((GLFWwindow *) m_Window);
    }

    void OpenGLRenderContext::Clear(const glm::vec4 &color)
    {
        PT_ASSERT(s_GladInitialized, "OpenGLRenderContext::Clear() called before OpenGLRenderContext::Init()!");
        glClearColor(color.r, color.g, color.b, color.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRenderContext::MakeCurrent()
    {
        glfwMakeContextCurrent((GLFWwindow *) m_Window);
    }
}