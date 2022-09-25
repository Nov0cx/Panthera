#include "Shader.hpp"

#ifdef PANTHERA_OPENGL
#include "Panthera/Platform/OpenGL/Shader/OpenGLShader.hpp"
#endif

namespace Panthera
{

    Ref <Shader> Shader::Create(const String &filepath)
    {
#ifdef PANTHERA_OPENGL
        return Ref<OpenGLShader>::Create(filepath);
#else
        PT_ASSERT(false, "Not a valid renderer API!");
        return nullptr;
#endif
    }

    Ref <Shader> Shader::Create(const String &filepath, const String& name)
    {
#ifdef PANTHERA_OPENGL
        return Ref<OpenGLShader>::Create(filepath, name);
#else
        PT_ASSERT(false, "Not a valid renderer API!");
        return nullptr;
#endif
    }

    Ref <Shader> Shader::Create(const String& name, const std::initializer_list<const String> &src)
    {
#ifdef PANTHERA_OPENGL
        return Ref<OpenGLShader>::Create(name, src);
#else
        PT_ASSERT(false, "Not a valid renderer API!");
        return nullptr;
#endif
    }

    static std::unordered_map <String, Ref <Shader>> s_Shaders;

    Ref <Shader> ShaderLibrary::Load(const String &filepath)
    {
        auto shader = Shader::Create(filepath);
        auto fileName = std::filesystem::path((std::string)filepath).filename().string();
        auto name = fileName.substr(0, fileName.find_last_of('.'));
        return s_Shaders[name] = shader;
    }

    Ref <Shader> ShaderLibrary::Load(const String &name, const String &filepath)
    {
        auto shader = Shader::Create(filepath, name);
        return s_Shaders[name] = shader;
    }

    Ref <Shader> ShaderLibrary::Load(const String &name, const std::initializer_list<const String> &src)
    {
        auto shader = Shader::Create(name, src);
        return s_Shaders[name] = shader;
    }

    Ref <Shader> ShaderLibrary::Get(const String &name)
    {
        return s_Shaders[name];
    }

    bool ShaderLibrary::Exists(const String &name)
    {
        return s_Shaders.contains(name);
    }
}