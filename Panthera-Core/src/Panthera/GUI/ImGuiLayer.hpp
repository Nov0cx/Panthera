#ifndef PANTHERA_IMGUILAYER_HPP
#define PANTHERA_IMGUILAYER_HPP

#include "Panthera/Core/Layer.hpp"
#include <imgui.h>

namespace Panthera
{
    // fwd
    class ImGuiHelper;

    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer() = default;
        ~ImGuiLayer() = default;

        virtual void OnStart() override;
        virtual void OnEnd() override;
        virtual void OnUpdate(Timestep ts) override;
        virtual void OnEvent(Event &event) override;
        void Begin();
        void End();

        void SetIniPath(const std::string& path);
    private:
        ImGuiHelper *m_ImGuiHelper;
    };

    class ImGuiHelper
    {
    public:
        virtual void Begin() = 0;
        virtual void End() = 0;
        virtual void OnStart() = 0;
        virtual void OnEnd() = 0;
    private:
    };
}

#endif //PANTHERA_IMGUILAYER_HPP
