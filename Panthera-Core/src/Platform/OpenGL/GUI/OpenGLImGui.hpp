#ifndef PANTHERA_OPENGLIMGUI_HPP
#define PANTHERA_OPENGLIMGUI_HPP

#include "Panthera/GUI/ImGuiLayer.hpp"

namespace Panthera
{
    class OpenGLImGui : public ImGuiHelper
    {
    public:
        OpenGLImGui();
        ~OpenGLImGui();
        virtual void Begin() override;
        virtual void End() override;
        virtual void OnStart() override;
        virtual void OnEnd() override;
    };
}

#endif //PANTHERA_OPENGLIMGUI_HPP
