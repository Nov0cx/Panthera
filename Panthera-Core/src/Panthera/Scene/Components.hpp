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

        glm::mat4 GetTransform()
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
    };
}

#endif //PANTHERA_COMPONENTS_HPP
