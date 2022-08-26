#ifndef PANTHERA_COMPONENTS_HPP
#define PANTHERA_COMPONENTS_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glm/gtx/quaternion.hpp>

#include "Panthera/Render/Texture/Texture.hpp"
#include "UUID.hpp"

namespace Panthera
{
    template<typename... Classes>
    struct ComponentGroup
    {
    };

    struct TransformComponent
    {
        glm::vec3 Translation = glm::vec3(0.0f);
        glm::vec3 Rotation = glm::vec3(0.0f);
        glm::vec3 Scale = glm::vec3(1.0f);

        TransformComponent() = default;
        TransformComponent(const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale)
            : Translation(translation), Rotation(rotation), Scale(scale)
        {
        }

        inline glm::mat4 GetTransform()
        {
            glm::mat4 rotationMatrix = glm::toMat4(glm::quat(Rotation));

            return glm::translate(glm::mat4(1.0f), Translation)
                   * rotationMatrix
                   * glm::scale(glm::mat4(1.0f), Scale);
        }
    };

    struct QuadComponent
    {
        glm::vec4 Color = glm::vec4(1.0f);

        float Tiling = 1.0f;
        Ref<Texture2D> Texture = nullptr;


        QuadComponent() = default;
        QuadComponent(const glm::vec4& color, float tiling = 1.0f, Ref<Texture2D> texture = nullptr)
            : Color(color), Texture(texture), Tiling(tiling)
        {
        }
    };

    struct CircleComponent
    {
        glm::vec4 Color = glm::vec4(1.0f);
        float BorderThickness = 1.0f;
        float Fade = 0.01f;

        float Tiling = 1.0f;
        Ref<Texture2D> Texture = nullptr;

        CircleComponent() = default;
        CircleComponent(const glm::vec4& color, float borderThickness = 1.0f, float fade = 0.01f, float tiling = 1.0f, Ref<Texture2D> texture = nullptr)
            : Color(color), BorderThickness(borderThickness), Fade(fade), Tiling(tiling), Texture(texture)
        {
        }
    };

    struct TriangleComponent
    {
        glm::vec4 Color = glm::vec4(1.0f);

        float Tiling = 1.0f;
        Ref<Texture2D> Texture = nullptr;

        TriangleComponent() = default;
        TriangleComponent(const glm::vec4& color, float tiling = 1.0f, Ref<Texture2D> texture = nullptr)
            : Color(color), Tiling(tiling), Texture(texture)
        {
        }
    };

    struct LineTransformComponent
    {
        glm::vec3 Start = glm::vec3(0.0f);
        glm::vec3 End = glm::vec3(0.0f);

        LineTransformComponent() = default;
        LineTransformComponent(const glm::vec3& start, const glm::vec3& end)
            : Start(start), End(end)
        {
        }
    };

    struct LineComponent
    {
        glm::vec4 Color = glm::vec4(1.0f);
        float Thickness = 1.0f;

        LineComponent() = default;
        LineComponent(const glm::vec4& color, float thickness = 1.0f)
            : Color(color), Thickness(thickness)
        {
        }
    };

    struct NameComponent
    {
        std::string Name;

        NameComponent() = default;
        NameComponent(const std::string& name)
            : Name(name)
        {
        }
    };

    struct IDComponent
    {
        UUID ID;

        IDComponent() = default;
        IDComponent(const UUID& id)
            : ID(id)
        {
        }
    };

    static constexpr ComponentGroup ALL_COMPONENTS = ComponentGroup<TransformComponent, QuadComponent, CircleComponent,
    TriangleComponent, LineTransformComponent, LineComponent, NameComponent, IDComponent>{};
}

#endif //PANTHERA_COMPONENTS_HPP
