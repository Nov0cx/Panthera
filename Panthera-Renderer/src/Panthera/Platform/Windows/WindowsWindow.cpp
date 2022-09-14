#include "WindowsWindow.hpp"

#include "ppch.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Panthera/Renderer/Renderer.hpp"

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
        }

        m_Window = glfwCreateWindow(m_Info.Width, m_Info.Height, m_Info.Title.Get(), nullptr, nullptr);
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

        // TODO: move
        glfwMakeContextCurrent((GLFWwindow*)m_Window);

        if (!gladLoadGL((GLADloadfunc) glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return;
        }

        SetVSync(m_Info.VSync);
        SetMaximized(m_Info.Maximized);
        SetFullScreen(m_Info.Fullscreen);
    }

    void WindowsWindow::Update()
    {
        if (m_IsShutDown)
            return;

        if (glfwWindowShouldClose((GLFWwindow*)m_Window))
            GlobalRenderer::RequestShutdown();

        glfwMakeContextCurrent((GLFWwindow*)m_Window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers((GLFWwindow*)m_Window);

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
            glfwGetWindowPos((GLFWwindow*)m_Window, &m_PosX, &m_PosY);

            GLFWmonitor *mon = monitor ? (GLFWmonitor*)monitor : glfwGetPrimaryMonitor();
            const GLFWvidmode *mode = glfwGetVideoMode(mon);
            glfwSetWindowMonitor((GLFWwindow*)m_Window, mon, 0, 0, mode->width, mode->height, mode->refreshRate);
        }
        else
        {
            GLFWmonitor *mon = monitor ? (GLFWmonitor*)monitor : glfwGetPrimaryMonitor();
            const GLFWvidmode *mode = glfwGetVideoMode(mon);
            glfwSetWindowMonitor((GLFWwindow*)m_Window, mon, m_PosX, m_PosY, m_Info.Width, m_Info.Height, mode->refreshRate);
        }
    }

    void WindowsWindow::SetMaximized(bool state)
    {
        m_Info.Maximized = state;
        if (state)
            glfwMaximizeWindow((GLFWwindow*)m_Window);
        else
            glfwRestoreWindow((GLFWwindow*)m_Window);
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

        glfwDestroyWindow((GLFWwindow*)m_Window);
        if (s_WindowCount-- <= 0)
        {
            glfwTerminate();
            s_InitGLFW = true;
        }
        s_WindowCount < 0 ? s_WindowCount = 0 : s_WindowCount;
        m_IsShutDown = true;
    }
}