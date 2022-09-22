#ifndef PANTHERA_SHADER_HPP
#define PANTHERA_SHADER_HPP

#include "ppch.hpp"

namespace Panthera
{
    class Shader
    {
    public:
        virtual void Bind() const = 0;
        virtual void* GetRenderObject() const = 0;
    private:
        static Ref<Shader> Create(const String& filepath);
        static Ref<Shader> Create(const String& filepath, const String& name);
        static Ref<Shader> Create(const String& name, const std::initializer_list<const String> &src);
        friend class ShaderLibrary;
    };

    class ShaderLibrary
    {
    public:
        static Ref<Shader> Load(const String& filepath);
        static Ref<Shader> Load(const String& name, const String& filepath);
        static Ref<Shader> Load(const String& name, const std::initializer_list<const String> &src);
        static Ref<Shader> Get(const String& name);
    };
}

#endif //PANTHERA_SHADER_HPP
