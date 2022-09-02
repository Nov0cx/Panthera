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
                                  bool selected = (m_SelectedEntity == entity);
                                  ImVec2 region = ImGui::GetContentRegionAvail();
                                  if (ImGui::Selectable(entity.GetName().c_str(), &selected))
                                  {

                                      if (m_SelectedEntity != entity)
                                          m_AddComponentPopup = false;

                                      m_SelectedEntity = entity;

                                      region = ImGui::GetContentRegionAvail();
                                  }

                                  if (ImGui::IsItemHovered())
                                  {
                                      if (ImGui::IsMouseDoubleClicked(0))
                                      {
                                          selected = false;
                                          m_SelectedEntity = {};
                                          m_AddComponentPopup = false;
                                      }
                                      if (ImGui::IsMouseClicked(1))
                                      {
                                          selected = true;
                                          m_AddComponentPopup = true;
                                      }
                                  }

                                  if (selected)
                                  {
                                      if (m_AddComponentPopup)
                                      {
                                          ImGui::OpenPopup("Add Component");
                                          if (ImGui::BeginPopup("Add Component"))
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
                                                  RenderComponentAddButton<LineTransformComponent>(entity,
                                                                                                   "LineTransform");
                                              if (!entity.HasComponent<LineComponent>() &&
                                                  !entity.HasComponent<TransformComponent>())
                                                  RenderComponentAddButton<LineComponent>(entity, "Line");

                                              ImGui::EndPopup();
                                          }

                                          if (!ImGui::IsItemHovered() && (ImGui::IsMouseClicked(1)))
                                              m_AddComponentPopup = false;
                                      }
                                  }
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
            ImGui::Separator();
        }

        if (entity.HasComponent<TransformComponent>())
        {
            if (ImGui::TreeNodeEx((void *) (uint64_t)
                    (((uint32_t)(entt::entity)
                entity.GetEntity()) +0), ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_OpenOnArrow,
                    "Transform"))
            {
                TransformComponent &transform = entity.GetComponent<TransformComponent>();
                ImGui::DragFloat3("Transform", &transform.Translation.x);
                glm::vec3 rotation = glm::degrees(transform.Rotation);
                ImGui::DragFloat3("Rotation", &rotation.x);
                transform.Rotation = glm::radians(rotation);
                ImGui::DragFloat3("Scale", &transform.Scale.x);
                ImGui::TreePop();
            }
            ImGui::Separator();
        }

        if (entity.HasComponent<QuadComponent>())
        {
            if (ImGui::TreeNodeEx((void *) (uint64_t)(((uint32_t)(entt::entity)entity.GetEntity()) +1),
            ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_OpenOnArrow,
                    "Quad"))
            {
                QuadComponent &quad = entity.GetComponent<QuadComponent>();
                ImGui::ColorEdit4("Color", &quad.Color.x);
                ImGui::TreePop();
            }
            ImGui::Separator();
        }

        if (entity.HasComponent<CircleComponent>())
        {
            if (ImGui::TreeNodeEx((void *) (uint64_t)(((uint32_t)(entt::entity)entity.GetEntity()) +2),
            ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_OpenOnArrow,
                    "Circle"))
            {
                CircleComponent &circle = entity.GetComponent<CircleComponent>();
                ImGui::ColorEdit4("Color", &circle.Color.x);
                ImGui::DragFloat("Border Thickness", &circle.BorderThickness);
                ImGui::DragFloat("Fade", &circle.Fade);
                ImGui::TreePop();
            }
            ImGui::Separator();
        }

        if (entity.HasComponent<TriangleComponent>())
        {
            if (ImGui::TreeNodeEx((void *) (uint64_t)(((uint32_t)(entt::entity)entity.GetEntity()) +3),
            ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_OpenOnArrow,
                    "Triangle"))
            {
                TriangleComponent &triangle = entity.GetComponent<TriangleComponent>();
                ImGui::ColorEdit4("Color", &triangle.Color.x);
                ImGui::TreePop();
            }
            ImGui::Separator();
        }

        if (entity.HasComponent<LineTransformComponent>())
        {
            if (ImGui::TreeNodeEx((void *) (uint64_t)(((uint32_t)(entt::entity)entity.GetEntity()) +4),
            ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_OpenOnArrow,
                    "Line Transform"))
            {
                LineTransformComponent &lineTransformComponent = entity.GetComponent<LineTransformComponent>();
                ImGui::DragFloat3("Start", &lineTransformComponent.Start.x);
                ImGui::DragFloat3("End", &lineTransformComponent.End.x);
                ImGui::TreePop();
            }
            ImGui::Separator();
        }

        if (entity.HasComponent<LineComponent>())
        {
            if (ImGui::TreeNodeEx((void *) (uint64_t)(((uint32_t)(entt::entity)entity.GetEntity()) +5),
            ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_OpenOnArrow,
                    "Line "))
            {
                LineComponent &line = entity.GetComponent<LineComponent>();
                ImGui::ColorEdit4("Color", &line.Color.x);
                ImGui::DragFloat("Thickness", &line.Thickness);
                ImGui::TreePop();
            }
            ImGui::Separator();
        }

        bool selected = false;
        ImGui::Selectable("Add Component", &selected);
        if (selected)
        {
            m_AddComponentPopup = true;
            selected = false;
        }

        ImGui::Separator();

        selected = false;
        ImGui::Selectable("Delete Entity", &selected);
        if (selected)
        {
            m_SelectedEntity.Destroy();
            m_SelectedEntity = {};
        }

        ImGui::Separator();


        ImGui::End();
    }
}