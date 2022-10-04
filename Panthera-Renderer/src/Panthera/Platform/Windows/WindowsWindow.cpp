#include "WindowsWindow.hpp"

#include "ppch.hpp"
#include <GLFW/glfw3.h>

#include "Panthera/Renderer/Renderer.hpp"
#include "Panthera/Event/EventSystem.hpp"
#include "Panthera/Event/WindowEvents.hpp"
#include "Panthera/Event/KeyboardEvents.hpp"
#include "Panthera/Event/MouseEvents.hpp"

namespace Panthera
{
    static bool s_InitGLFW = false;
    static uint32_t s_WindowCount = 0;

    WindowsWindow::WindowsWindow(const WindowInfo &info)
    {
        m_Info.Title = info.Title;
        m_Info.Width = info.Width;
        m_Info.Height = info.Height;
        m_Info.VSync = info.VSync;
        m_Info.Fullscreen = info.Fullscreen;
    }

    WindowsWindow::~WindowsWindow()
    {
        Shutdown();
    }

    void WindowsWindow::Init()
    {
        s_WindowCount++;
        if (!s_InitGLFW)
        {
            PT_ASSERT(glfwInit(), "Failed to init GLFW!");

            s_InitGLFW = true;
        } else
        {
            PT_LOG_INFO("GLFW already initialized!");
        }

        PT_LOG_INFO("Creating window {} ({}, {})", m_Info.Title, m_Info.Width, m_Info.Height);

        bool share = s_WindowCount > 1;

        PT_LOG_DEBUG("Sharing context: {}", share);

        GLFWwindow *shareWindow = share ? (GLFWwindow*)GlobalRenderer::GetMainWindow()->GetNativeWindow() : nullptr;

        m_Window = glfwCreateWindow(m_Info.Width, m_Info.Height, m_Info.Title.Get(), nullptr, shareWindow);
        if (!m_Window)
        {
            PT_LOG_FATAL("Failed to create GLFW window!");
            Shutdown();
            return;
        }

        //glfwSetWindowUserPointer((GLFWwindow*)m_Window, &m_Info);

        glfwSetErrorCallback([](int error, const char *description)
                             {
                                 PT_LOG_ERROR("GLFW error: {}", description);
                             });

        m_Context = RenderContext::Create((GLFWwindow*)m_Window);
        m_Context->Init();
        m_Context->MakeCurrent();

        glfwSetWindowSizeCallback((GLFWwindow*)m_Window, [](GLFWwindow *window, int width, int height)
        {
            WindowResizeEvent resizeEvent {width, height};
            EventManager::DispatchEvent(resizeEvent);
        });

        glfwSetWindowCloseCallback((GLFWwindow*)m_Window, [](GLFWwindow *window)
        {
            WindowCloseEvent closeEvent = WindowCloseEvent();
            EventManager::DispatchEvent(closeEvent);
        });

        glfwSetKeyCallback((GLFWwindow*)m_Window, [](GLFWwindow *window, int key, int scancode, int action, int mods)
        {
            switch (action)
            {
                case GLFW_PRESS:
                {
                    KeyPressedEvent keyEvent = KeyPressedEvent(key, 0);
                    EventManager::DispatchEvent(keyEvent);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent keyEvent = KeyReleasedEvent(key);
                    EventManager::DispatchEvent(keyEvent);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent keyEvent = KeyPressedEvent(key, 1);
                    EventManager::DispatchEvent(keyEvent);
                    break;
                }
            }
        });

        glfwSetCharCallback((GLFWwindow*)m_Window, [](GLFWwindow *window, unsigned int keycode)
        {
            KeyTypedEvent keyEvent = KeyTypedEvent(keycode);
            EventManager::DispatchEvent(keyEvent);
        });

        glfwSetMouseButtonCallback((GLFWwindow*)m_Window, [](GLFWwindow *window, int button, int action, int mods)
        {
            switch (action)
            {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent mouseEvent = MouseButtonPressedEvent(button);
                    EventManager::DispatchEvent(mouseEvent);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent mouseEvent = MouseButtonReleasedEvent(button);
                    EventManager::DispatchEvent(mouseEvent);
                    break;
                }
            }
        });

        glfwSetScrollCallback((GLFWwindow*)m_Window, [](GLFWwindow *window, double xOffset, double yOffset)
        {
            MouseScrollEvent mouseEvent = MouseScrollEvent((float)xOffset, (float)yOffset);
            EventManager::DispatchEvent(mouseEvent);
        });

        glfwSetCursorPosCallback((GLFWwindow*)m_Window, [](GLFWwindow *window, double xPos, double yPos)
        {
            MouseMoveEvent mouseEvent = MouseMoveEvent((float)xPos, (float)yPos);
            EventManager::DispatchEvent(mouseEvent);
        });

        SetVSync(m_Info.VSync);
        SetMaximized(m_Info.Maximized);
        SetFullScreen(m_Info.Fullscreen);
    }

    void WindowsWindow::Update()
    {
        if (m_IsShutDown)
            return;

        if (glfwWindowShouldClose((GLFWwindow *) m_Window))
            if (GlobalRenderer::RequestShutdownWindow(this))
            {
                Shutdown();
                return;
            }

        m_Context->MakeCurrent();

        m_Context->SwapBuffers();
        glfwPollEvents();
    }

    void *WindowsWindow::GetNativeWindow()
    {
        return m_Window;
    }

    void WindowsWindow::SetFullScreen(bool state, void *monitor)
    {
        if (state == m_Info.Fullscreen)
            return;

        m_Info.Fullscreen = state;

        if (state)
        {
            glfwGetWindowPos((GLFWwindow *) m_Window, &m_PosX, &m_PosY);

            GLFWmonitor *mon = monitor ? (GLFWmonitor *) monitor : glfwGetPrimaryMonitor();
            const GLFWvidmode *mode = glfwGetVideoMode(mon);
            glfwSetWindowMonitor((GLFWwindow *) m_Window, mon, 0, 0, mode->width, mode->height, mode->refreshRate);
        } else
        {
            GLFWmonitor *mon = monitor ? (GLFWmonitor *) monitor : glfwGetPrimaryMonitor();
            const GLFWvidmode *mode = glfwGetVideoMode(mon);
            glfwSetWindowMonitor((GLFWwindow *) m_Window, mon, m_PosX, m_PosY, m_Info.Width, m_Info.Height,
                                 mode->refreshRate);
        }
    }

    void WindowsWindow::SetMaximized(bool state)
    {
        m_Info.Maximized = state;
        if (state)
            glfwMaximizeWindow((GLFWwindow *) m_Window);
        else
            glfwRestoreWindow((GLFWwindow *) m_Window);
    }

    void WindowsWindow::SetVSync(bool enabled)
    {
        m_Info.VSync = enabled;
        if (enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);
    }

    bool WindowsWindow::IsVSync() const
    {
        return m_Info.VSync;
    }

    WindowInfo &WindowsWindow::GetInfo()
    {
        return m_Info;
    }

    const WindowInfo &WindowsWindow::GetInfo() const
    {
        return m_Info;
    }

    void WindowsWindow::Shutdown()
    {
        if (m_IsShutDown)
            return;

        glfwDestroyWindow((GLFWwindow *) m_Window);
        if (s_WindowCount-- <= 0)
        {
            glfwTerminate();
            s_InitGLFW = true;
        }
        s_WindowCount < 0 ? s_WindowCount = 0 : s_WindowCount;
        m_IsShutDown = true;
    }

    Ref <RenderContext> WindowsWindow::GetRenderContext() const
    {
        return m_Context;
    }

    bool WindowsWindow::operator==(const Window &other) const
    {
        return m_Window == ((const WindowsWindow&)other).m_Window;
    }

    bool WindowsWindow::operator!=(const Window &other) const
    {
        return !(*this == other);
    }
}