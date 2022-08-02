#ifndef PANTHERA_SHADER_HPP
#define PANTHERA_SHADER_HPP

#include "Panthera/Core/Pointer.hpp"
#include <string>
#include <unordered_map>

namespace Panthera
{
    // fwd
    class ShaderLibrary;

    using RendererID = uint32_t;

    class Shader
    {
    public:
        virtual ~Shader() = default;
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual RendererID GetRendererID() const = 0;
    private:
        static Ref<Shader> Create(const std::string &vertexSrc, const std::string &fragmentSrc);
        static Ref<Shader> Create(const std::string &path);
        friend class ShaderLibrary;
    };

    class ShaderLibrary
    {
    public:
        ShaderLibrary() = default;
        ~ShaderLibrary() = default;

        Ref<Shader> CreateShader(const std::string &name, const std::string &vertexSrc, const std::string &fragmentSrc);
        Ref<Shader> CreateShader(const std::string &name, const std::string &path);
        Ref<Shader> GetShader(const std::string &name);



    private:
        std::unordered_map<std::string, Ref<Shader>> m_Shaders;
    };

}

#endif //PANTHERA_SHADER_HPP
