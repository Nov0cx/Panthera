#include "SceneHierarchyPanel.hpp"

namespace Panthera
{

    SceneHierarchyPanel::SceneHierarchyPanel(Scene *scene)
    {
        m_Scene = scene;
    }

    SceneHierarchyPanel::~SceneHierarchyPanel()
    {}

    void SceneHierarchyPanel::Render()
    {
        ImGui::Begin("Scene Hierarchy");
        m_Scene->ForAllEntities([this](SceneEntity& entity)
        {
            if (ImGui::TreeNode(entity.GetName().c_str()))
            {
                ImGui::TreePop();
            }
        });
        ImGui::End();
    }
}