#include "GLFWWindow.hpp"

#include "Panthera/Core/Log.hpp"
#include <GLFW/glfw3.h>
#include "Panthera/Events/KeyEvents.hpp"
#include "Panthera/Events/MouseEvents.hpp"
#include "Panthera/Events/WindowEvents.hpp"
#include "Panthera/Core/Application.hpp"

namespace Panthera
{
    GLFWWindow::GLFWWindow(const WindowProps &props)
    {
        m_Info = {props.Width, props.Height, props.Title, props.VSync};

        Init(props.Title, props.Width, props.Height);
    }

    void GLFWWindow::Init(const char *title, uint32_t width, uint32_t height)
    {
        bool need_init = p_WindowCount == 0;

        if (need_init)
        {
            ASSERT(glfwInit(), "Failed to init GLFW!")
        }
        p_WindowCount++;

        m_Window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!m_Window)
        {
            FAIL("Failed to create GLFW window!")
        }

        m_Context = RenderContext::Create(m_Window);
        m_Context->MakeContext();

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

#ifdef PANTHERA_DEBUG
        glfwSetErrorCallback([](int error, const char *description)
        {
            LOG_ERROR("GLFW error: {}", description)
        });
#endif

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

        SetVSync(m_Info.VSync);
    }

    GLFWWindow::~GLFWWindow()
    {
        if (p_WindowCount-- == 0)
        {
            glfwTerminate();
        }
    }

    void GLFWWindow::OnEvent(Event &event)
    {

    }

    std::any GLFWWindow::GetNativeWindow() const
    {
        return m_Window;
    }

    uint32_t GLFWWindow::GetWidth() const
    {
        return m_Info.Width;
    }

    uint32_t GLFWWindow::GetHeight() const
    {
        return m_Info.Height;
    }

    void GLFWWindow::SetVSync(bool state)
    {
        m_Info.VSync = state;

        if (state)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);
    }

    bool GLFWWindow::IsVSync() const
    {
        return m_Info.VSync;
    }

    void GLFWWindow::OnUpdate()
    {
        m_Context->SwapBuffers();
        glfwPollEvents();
    }

    bool GLFWWindow::ShouldBeClosed() const
    {
        return glfwWindowShouldClose(m_Window);
    }
}