#ifndef PANTHERA_COMPONENTS_HPP
#define PANTHERA_COMPONENTS_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include "Panthera/Render/Texture/Texture.hpp"

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

        Ref<Texture2D> Texture = nullptr;
        float Tiling = 1.0f;

        QuadComponent() = default;
        QuadComponent(const glm::vec4& color)
            : Color(color)
        {
        }

        QuadComponent(const glm::vec4& color, Ref<Texture2D> texture = nullptr, float tiling = 1.0f)
            : Color(color), Texture(texture), Tiling(tiling)
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
}

#endif //PANTHERA_COMPONENTS_HPP
