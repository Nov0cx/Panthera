#include "SceneHierarchyPanel.hpp"

namespace Panthera
{

    SceneHierarchyPanel::SceneHierarchyPanel()
    {
    }

    SceneHierarchyPanel::~SceneHierarchyPanel()
    {}

    template<typename Component>
    static void RenderComponentAddButton(SceneEntity entity, const std::string &name)
    {
        if (ImGui::Button(("Add " + name).c_str()))
        {
            entity.CreateComponent<Component>();
        }
    }

    void SceneHierarchyPanel::Render(Scene *scene)
    {
        ImGui::Begin("Scene Hierarchy");

        if (ImGui::Button("Add Empty Entity"))
            scene->CreateEntity("Empty Entity");

        scene->ForAllEntities([this](SceneEntity &entity)
                              {
                                  /*bool opened = ImGui::TreeNodeEx((void *) (uint64_t)(uint32_t)(entt::entity)
                                  entity.GetEntity(), ImGuiTreeNodeFlags_SpanAvailWidth |
                                                      ((m_SelectedEntity == entity) ? ImGuiTreeNodeFlags_Selected
                                                                                    : 0) | ImGuiTreeNodeFlags_OpenOnArrow, entity.GetName().c_str());*/

                                  bool selected = (m_SelectedEntity == entity);
                                  ImVec2 region = ImGui::GetContentRegionAvail();

                                  if (ImGui::Selectable(entity.GetName().c_str(), &selected)) {

                                      m_SelectedEntity = entity;

                                      region = ImGui::GetContentRegionAvail();
                                  }

                                  if (selected)
                                  {
                                      ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{4, 5});

                                      float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
                                      ImGui::SameLine(region.x - lineHeight * 1.35f);

                                      if (ImGui::Button("+", ImVec2{ lineHeight, lineHeight }))
                                      {
                                          ImGui::OpenPopup("Add Component");
                                      }

                                      if (ImGui::BeginPopup("AddComponent"))
                                      {
                                          if (!entity.HasComponent<TransformComponent>() &&
                                              !entity.HasComponent<LineTransformComponent>())
                                              RenderComponentAddButton<TransformComponent>(entity, "Transform");
                                          if (!entity.HasComponent<QuadComponent>() &&
                                              !entity.HasComponent<LineTransformComponent>())
                                              RenderComponentAddButton<QuadComponent>(entity, "Quad");
                                          if (!entity.HasComponent<CircleComponent>() &&
                                              !entity.HasComponent<LineTransformComponent>())
                                              RenderComponentAddButton<CircleComponent>(entity, "Circle");
                                          if (!entity.HasComponent<TriangleComponent>() &&
                                              !entity.HasComponent<LineTransformComponent>())
                                              RenderComponentAddButton<TriangleComponent>(entity, "Triangle");
                                          if (!entity.HasComponent<LineTransformComponent>() &&
                                              !entity.HasComponent<TransformComponent>())
                                              RenderComponentAddButton<LineTransformComponent>(entity, "LineTransform");
                                          if (!entity.HasComponent<LineComponent>() &&
                                              !entity.HasComponent<TransformComponent>())
                                              RenderComponentAddButton<LineComponent>(entity, "Line");

                                          ImGui::EndPopup();
                                      }
                                      ImGui::PopStyleVar();

                                      ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{9, 5});

                                      ImGui::SameLine(region.x - lineHeight * 0.35f);
                                      lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;

                                      if (ImGui::Button("-", ImVec2{lineHeight, lineHeight}))
                                      {
                                          entity.Destroy();
                                      }

                                      ImGui::PopStyleVar();
                                  }
                                  /*if (ImGui::IsItemClicked())
                                      m_SelectedEntity = entity;*/


                                  /*if (opened)
                                  {
                                      ImGuiTreeNodeFlags flags =
                                              ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
                                      bool opened = ImGui::TreeNodeEx((void *) 9817239, flags,
                                                                      entity.GetName().c_str());
                                      if (opened)
                                          ImGui::TreePop();
                                      ImGui::TreePop();
                                  }*/
                              });
        ImGui::End();
        DrawSelectedEntityProperties(scene);
    }

    void SceneHierarchyPanel::DrawSelectedEntityProperties(Scene *scene)
    {
        ImGui::Begin("Entity Properties");
        if (!m_SelectedEntity)
        {
            ImGui::End();
            return;
        }

        SceneEntity entity = m_SelectedEntity;

        if (entity.HasComponent<NameComponent>())
        {
            auto &name = entity.GetComponent<NameComponent>().Name;

            char buffer[256];
            memset(buffer, 0, sizeof(buffer));
            std::strncpy(buffer, name.c_str(), sizeof(buffer));
            if (ImGui::InputText("Name", buffer, sizeof(buffer)))
            {
                if (strlen(buffer) > 0)
                    name = std::string(buffer);
            }
        }

        if (entity.HasComponent<TransformComponent>())
        {
            if (ImGui::TreeNodeEx((void *) (uint64_t)(uint32_t)(entt::entity)
                entity.GetEntity(), ImGuiTreeNodeFlags_SpanAvailWidth, "Transform")) {
                TransformComponent &transform = entity.GetComponent<TransformComponent>();
                ImGui::DragFloat3("Transform", &transform.Translation.x);
                glm::vec3 rotation = glm::degrees(transform.Rotation);
                ImGui::DragFloat3("Rotation", &rotation.x);
                transform.Rotation = glm::radians(rotation);
                ImGui::DragFloat3("Scale", &transform.Scale.x);
                ImGui::Separator();
                ImGui::TreePop();
            }
        }
        if (entity.HasComponent<QuadComponent>())
        {
            if (ImGui::TreeNodeEx((void *) (uint64_t)(uint32_t)(entt::entity)
                entity.GetEntity(), ImGuiTreeNodeFlags_SpanAvailWidth, "Quad")) {
                QuadComponent &quad = entity.GetComponent<QuadComponent>();
                ImGui::ColorEdit4("Color", &quad.Color.x);
                ImGui::Separator();
                ImGui::TreePop();
            }
        }
        if (entity.HasComponent<CircleComponent>())
        {
            if (ImGui::TreeNodeEx((void *) (uint64_t)(uint32_t)(entt::entity)
                entity.GetEntity(), ImGuiTreeNodeFlags_SpanAvailWidth, "Circle")) {
                CircleComponent &circle = entity.GetComponent<CircleComponent>();
                ImGui::ColorEdit4("Color", &circle.Color.x);
                ImGui::DragFloat("Border Thickness", &circle.BorderThickness);
                ImGui::DragFloat("Fade", &circle.Fade);
                ImGui::Separator();
                ImGui::TreePop();
            }
        }
        if (entity.HasComponent<TriangleComponent>())
        {
            if (ImGui::TreeNodeEx((void *) (uint64_t)(uint32_t)(entt::entity)
                entity.GetEntity(), ImGuiTreeNodeFlags_SpanAvailWidth, "Triangle")) {
                TriangleComponent &triangle = entity.GetComponent<TriangleComponent>();
                ImGui::ColorEdit4("Color", &triangle.Color.x);
                ImGui::Separator();
                ImGui::TreePop();
            }
        }
        if (entity.HasComponent<LineTransformComponent>())
        {
            if (ImGui::TreeNodeEx((void *) (uint64_t)(uint32_t)(entt::entity)
                entity.GetEntity(), ImGuiTreeNodeFlags_SpanAvailWidth, "Line Transform")) {
                LineTransformComponent &lineTransformComponent = entity.GetComponent<LineTransformComponent>();
                ImGui::DragFloat3("Start", &lineTransformComponent.Start.x);
                ImGui::DragFloat3("End", &lineTransformComponent.End.x);
                ImGui::Separator();
                ImGui::TreePop();
            }
        }
        if (entity.HasComponent<LineComponent>())
        {
            if (ImGui::TreeNodeEx((void *) (uint64_t)(uint32_t)(entt::entity)
                entity.GetEntity(), ImGuiTreeNodeFlags_SpanAvailWidth, "Line ")) {
                LineComponent &line = entity.GetComponent<LineComponent>();
                ImGui::ColorEdit4("Color", &line.Color.x);
                ImGui::DragFloat("Thickness", &line.Thickness);
                ImGui::Separator();
                ImGui::TreePop();
            }
        }

        ImGui::End();
    }
}