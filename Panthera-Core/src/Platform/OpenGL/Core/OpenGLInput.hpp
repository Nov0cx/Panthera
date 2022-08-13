#ifndef PANTHERA_OPENGLINPUT_HPP
#define PANTHERA_OPENGLINPUT_HPP

#include "Panthera/Window/Window.hpp"
#include "Panthera/Core/Input.hpp"

namespace Panthera
{
    class OpenGLInput
    {
    public:
        static bool IsKeyPressed(Ref<Window> &window, Key key);

    };
}

#endif //PANTHERA_OPENGLINPUT_HPP
