#include "WindowsWindow.hpp"

#include "ppch.hpp"
#include <GLFW/glfw3.h>

namespace Panthera
{
    static bool s_InitGLFW = false;

    WindowsWindow::WindowsWindow(const WindowInfo &info)
    {
        m_Info.Title = info.Title;
        m_Info.Width = info.Width;
        m_Info.Height = info.Height;
        m_Info.VSync = info.VSync;
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

        m_Window = glfwCreateWindow(m_Info.Width, m_Info.Height, m_Info.Title.CStr(), nullptr, nullptr);
        if (!m_Window)
        {
            PT_FATAL("Failed to create GLFW window!");
            Shutdown();
            return;
        }

        glfwSetWindowUserPointer(m_Window, &m_Info);

        glfwSetErrorCallback([](int error, const char *description)
        {
            PT_ERROR("GLFW error: {}", description);
        });
    }

    void WindowsWindow::Update()
    {
        if (m_IsShutDown)
            return;
    }

    void *WindowsWindow::GetNativeWindow()
    {
        return NULL;
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
        if (s_WindowCount-- <=)
        {
            glfwTerminate();
            s_InitGLFW = true;
        }
        s_WindowCount < 0 ? s_WindowCount = 0 : s_WindowCount;
        m_IsShutDown = true;
    }
}