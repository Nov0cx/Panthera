#include "OpenGLWindow.hpp"

#include "Panthera/Core/Log.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Panthera
{

    OpenGLWindow::OpenGLWindow(const WindowProps &props)
    {
        m_Height = props.Height;
        m_Width = props.Width;
        m_VSync = props.VSync;

        Init(props.Title, m_Width, m_Height);
    }

    void OpenGLWindow::Init(const char *title, uint32_t width, uint32_t height)
    {
        bool need_init = p_WindowCount == 0;

        if (need_init)
        {
            ASSERT(glfwInit(), "Failed to init GLFW!")
        }
        p_WindowCount++;

        m_Window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        ASSERT(m_Window, "Failed to create GLFW window!")



        m_Context = RenderContext::Create(m_Window);
        m_Context->MakeContext();

        if (need_init)
        {
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            {
                glfwTerminate();
                ASSERT(false, "Failed to initialize GLAD!")
            }
        }

        if (GLAD_GL_VERSION_4_6)
        {
            LOG_DEBUG("OpenGL 4.6 is supported!")
        } else {
            ASSERT(false, "OpenGL 4.6 is not supported!")
        }

        LOG_DEBUG("OpenGL Version: {}", (char*)glGetString(GL_VERSION));
    }

    OpenGLWindow::~OpenGLWindow()
    {
        if (p_WindowCount-- == 0)
        {
            glfwTerminate();
        }
    }

    void OpenGLWindow::OnEvent(Event &event)
    {

    }

    std::any OpenGLWindow::GetNativeWindow() const
    {
        return m_Window;
    }

    uint32_t OpenGLWindow::GetWidth() const
    {
        return m_Width;
    }

    uint32_t OpenGLWindow::GetHeight() const
    {
        return m_Height;
    }

    void OpenGLWindow::SetVSync(bool state)
    {
        m_VSync = state;

        if (state)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);
    }

    bool OpenGLWindow::IsVSync() const
    {
        return m_VSync;
    }

    void OpenGLWindow::OnUpdate()
    {
        m_Context->SwapBuffers();
        glfwPollEvents();
    }

    bool OpenGLWindow::ShouldBeClosed() const
    {
        return glfwWindowShouldClose(m_Window);
    }
}