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
        static Ref<Shader> Create(const std::string& name, const std::string &vertexSrc, const std::string &fragmentSrc);
        static Ref<Shader> Create(const std::string &path);
        friend class ShaderLibrary;
    };

    class ShaderLibrary
    {
    public:
        static Ref<Shader> CreateShader(const std::string &name, const std::string &vertexSrc, const std::string &fragmentSrc);
        static Ref<Shader> CreateShader(const std::string &name, const std::string &path);
        static Ref<Shader> GetShader(const std::string &name);

    private:
        ShaderLibrary() = default;
        ~ShaderLibrary() = default;
    };

}

#endif //PANTHERA_SHADER_HPP
