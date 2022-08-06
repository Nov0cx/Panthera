#include "OpenGLWindow.hpp"

#include "Panthera/Core/Log.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Panthera/Events/KeyEvents.hpp"
#include "Panthera/Events/MouseEvents.hpp"
#include "Panthera/Events/WindowEvents.hpp"
#include "Panthera/Core/Application.hpp"

namespace Panthera
{

    OpenGLWindow::OpenGLWindow(const WindowProps &props)
    {
        m_Info = {props.Width, props.Height, props.Title, props.VSync};

        Init(props.Title, props.Width, props.Height);
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
            if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
            {
                glfwTerminate();
                ASSERT(false, "Failed to initialize GLAD!")
            }
        }

        if (GLAD_GL_VERSION_4_6)
        {
            LOG_DEBUG("OpenGL 4.6 is supported!")
        }
        else
        {
            ASSERT(false, "OpenGL 4.6 is not supported!")
        }

        LOG_DEBUG("OpenGL Version: {}", (char *) glGetString(GL_VERSION));

        glfwSetWindowUserPointer(m_Window, &m_Info);

        glfwSetErrorCallback([](int error, const char *description)
        {
            LOG_ERROR("GLFW error: {}", description)
        });

        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow *window, int width, int height)
        {
            WindowResizeEvent resizeEvent = WindowResizeEvent{width, height};
            Application::GetInstance()->CallEvent(resizeEvent);

            WindowInfo &info = *(WindowInfo *) glfwGetWindowUserPointer(window);
            info.Height = height;
            info.Width = width;

            if (width != resizeEvent.Width || height != resizeEvent.Height)
                glfwSetWindowSize(window, resizeEvent.Width, resizeEvent.Height);
        });

        /*glfwSetWindowCloseCallback(m_Window, [](GLFWwindow *window)
        {
        });*/

        glfwSetKeyCallback(m_Window, [](GLFWwindow *window, int key, int scancode, int action, int mods)
        {
            if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
                glfwSetWindowShouldClose(window, GLFW_TRUE);

            switch (action)
            {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(key, false);
                    Application::GetInstance()->CallEvent(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
                    Application::GetInstance()->CallEvent(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key, true);
                    Application::GetInstance()->CallEvent(event);
                    break;
                }
            }
        });

        glfwSetCharCallback(m_Window, [](GLFWwindow *window, unsigned int keycode)
        {
            KeyTypedEvent event(keycode);
            Application::GetInstance()->CallEvent(event);
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow *window, int button, int action, int mods)
        {
            switch (action)
            {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button);
                    Application::GetInstance()->CallEvent(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(button);
                    Application::GetInstance()->CallEvent(event);
                    break;
                }
            }
        });

        glfwSetScrollCallback(m_Window, [](GLFWwindow *window, double xOffset, double yOffset)
        {
            MouseScrollEvent event(xOffset, yOffset);
            Application::GetInstance()->CallEvent(event);
        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow *window, double xPos, double yPos)
        {
            MouseMoveEvent event(xPos, yPos);
            Application::GetInstance()->CallEvent(event);
        });
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
        return m_Info.Width;
    }

    uint32_t OpenGLWindow::GetHeight() const
    {
        return m_Info.Height;
    }

    void OpenGLWindow::SetVSync(bool state)
    {
        m_Info.VSync = state;

        if (state)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);
    }

    bool OpenGLWindow::IsVSync() const
    {
        return m_Info.VSync;
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