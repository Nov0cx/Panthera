#include "ScenePanel.hpp"

namespace Panthera
{

    void ScenePanel::Render(Scene *scene)
    {
       ImGui::Begin("Scene Panel");
       ImGui::Text("Scene: %s", scene->GetName().c_str());

       ImGui::End();
    }
}