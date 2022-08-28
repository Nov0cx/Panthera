#ifndef PANTHERA_IMGUILAYER_HPP
#define PANTHERA_IMGUILAYER_HPP

#include "Panthera/Core/Layer.hpp"
#include <imgui.h>
#include <imgui_internal.h>

namespace Panthera
{
    // fwd
    class ImGuiHelper;

    enum class ImGuiThemes
    {
        Light,
        Classic,
        Dark,
        HazelEngine,
        Panthera,
    };

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

        void SetTheme(ImGuiThemes theme);

        void SetBlockEvents(bool blockEvents) { m_BlockEvents = blockEvents; }
    private:
        ImGuiHelper *m_ImGuiHelper;
        bool m_BlockEvents = false;
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
