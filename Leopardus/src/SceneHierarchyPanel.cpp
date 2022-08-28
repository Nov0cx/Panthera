#include "SceneHierarchyPanel.hpp"

namespace Panthera
{

    SceneHierarchyPanel::SceneHierarchyPanel(Scene *scene)
    {
        scene = scene;
    }

    SceneHierarchyPanel::~SceneHierarchyPanel()
    {}

    void SceneHierarchyPanel::Render(Scene* scene)
    {
        ImGui::Begin("Scene Hierarchy");
        scene->ForAllEntities([this](SceneEntity& entity)
        {
            if (ImGui::TreeNode(entity.GetName().c_str()))
            {
                ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();
                float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
                ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
                ImGui::SameLine(contentRegionAvailable.x - lineHeight * 0.35f);
                if (ImGui::Button("+", ImVec2{ lineHeight, lineHeight }))
                {
                    ImGui::OpenPopup("ComponentSettings");
                }
                ImGui::PopStyleVar();
                ImGui::Separator();
                if (entity.HasComponent<TransformComponent>())
                {
                    TransformComponent& transform = entity.GetComponent<TransformComponent>();
                    ImGui::DragFloat3("Transform", &transform.Translation.x);
                    glm::vec3 rotation = glm::degrees(transform.Rotation);
                    ImGui::DragFloat3("Rotation", &rotation.x);
                    transform.Rotation = glm::radians(rotation);
                    ImGui::DragFloat3("Scale", &transform.Scale.x);
                    ImGui::Separator();
                }
                if (entity.HasComponent<QuadComponent>())
                {
                    QuadComponent& quad = entity.GetComponent<QuadComponent>();
                    ImGui::ColorEdit4("Color", &quad.Color.x);
                    ImGui::Separator();
                }
                if (entity.HasComponent<CircleComponent>())
                {
                    CircleComponent& circle = entity.GetComponent<CircleComponent>();
                    ImGui::ColorEdit4("Color", &circle.Color.x);
                    ImGui::DragFloat("Border Thickness", &circle.BorderThickness);
                    ImGui::DragFloat("Fade", &circle.Fade);
                    ImGui::Separator();
                }
                if (entity.HasComponent<TriangleComponent>())
                {
                    TriangleComponent& triangle = entity.GetComponent<TriangleComponent>();
                    ImGui::ColorEdit4("Color", &triangle.Color.x);
                    ImGui::Separator();
                }
                if (entity.HasComponent<LineTransformComponent>())
                {
                    LineTransformComponent& lineTransformComponent = entity.GetComponent<LineTransformComponent>();
                    ImGui::DragFloat3("Start", &lineTransformComponent.Start.x);
                    ImGui::DragFloat3("End", &lineTransformComponent.End.x);
                    ImGui::Separator();
                }
                if (entity.HasComponent<LineComponent>())
                {
                    LineComponent& line = entity.GetComponent<LineComponent>();
                    ImGui::ColorEdit4("Color", &line.Color.x);
                    ImGui::DragFloat("Thickness", &line.Thickness);
                    ImGui::Separator();
                }
                ImGui::TreePop();
            }
        });
        ImGui::End();
    }
}