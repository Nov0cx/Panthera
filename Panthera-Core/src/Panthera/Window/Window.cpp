#include "Window.hpp"

#include "Panthera/Render/Renderer.hpp"
#include "Panthera/Core/Log.hpp"
#include "Panthera/Core/Pointer.hpp"
#include "Platform/GLFW/Window/GLFWWindow.hpp"

namespace Panthera
{
    Ref<Window> Window::Create(const Panthera::WindowProps &props)
    {
        switch (RendererState::GetAPI())
        {
            case RendererAPI::OpenGL:
                return CreateRef<GLFWWindow>(props);
            case RendererAPI::Vulkan:
                LOG_WARN("Vulkan Window is not supported yet!");
                break;
            case RendererAPI::None:
                LOG_WARN("Window with RendererAPI is not supported yet!");
                break;
            case RendererAPI::Direct3D:
                LOG_WARN("Direct3D Window is not supported yet!");
                break;
            case RendererAPI::Metal:
                LOG_WARN("Metal Window is not supported yet!");
                break;
            case RendererAPI::OpenGLES:
                LOG_WARN("OpenGLES Window is not supported yet!");
                break;
            default:
                ASSERT(false, "Unknown RendererAPI! {}", (int)RendererState::GetAPI());
        }

        ASSERT(false, "Not Supported RendererAPI")
    }

    WindowProps::WindowProps(const char *title, const uint32_t &width, const uint32_t &height, bool vSync) : Title(
            title), Width(width), Height(height), VSync(vSync)
    {}
}

