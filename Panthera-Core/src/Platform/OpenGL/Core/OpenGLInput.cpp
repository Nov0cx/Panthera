#include "OpenGLInput.hpp"
#include <GLFW/glfw3.h>

#include <any>

namespace Panthera
{
    bool OpenGLInput::IsKeyPressed(Ref<Window> &window, Key key)
    {
        GLFWwindow *windowHandle = std::any_cast<GLFWwindow *>(window->GetNativeWindow());
        int state = glfwGetKey(windowHandle, (int)key);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }
}