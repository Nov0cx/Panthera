#include "Input.hpp"

#include "Panthera/Render/Renderer.hpp"
#include "Platform/OpenGL/Core/OpenGLInput.hpp"
#include "Application.hpp"

namespace Panthera
{

    bool Input::IsKeyPressed(Key key)
    {
        switch (RendererState::GetAPI())
        {
            case RendererAPI::OpenGL:
                return OpenGLInput::IsKeyPressed(Application::GetInstance()->GetWindow(), key);
            case RendererAPI::None:
                ASSERT(false, "RendererAPI::None is not supported!")
            case RendererAPI::Vulkan:
                ASSERT(false, "RendererAPI::Vulkan is not supported!")
            case RendererAPI::Direct3D:
                ASSERT(false, "RendererAPI::Direct3D is not supported!")
            case RendererAPI::Metal:
                ASSERT(false, "RendererAPI::Metal is not supported!")
            case RendererAPI::OpenGLES:
                ASSERT(false, "RendererAPI::OpenGLES is not supported!")
        }
    }
}