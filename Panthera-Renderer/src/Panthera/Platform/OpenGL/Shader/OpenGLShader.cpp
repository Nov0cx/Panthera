#include "OpenGLShader.hpp"

#include <shaderc/shaderc.hpp>
#include <spirv_cross/spirv_cross.hpp>
#include <spirv_cross/spirv_glsl.hpp>
#include <glad/glad.h>

namespace Panthera
{

    static constexpr const char* GetCachePath()
    {
        return "./.cache/shaders/opengl/";
    }

    static constexpr const char* GetCacheShaderExtension(GLenum shader)
    {
        switch (shader)
        {
            case GL_VERTEX_SHADER:
                return ".vert.cached";
            case GL_FRAGMENT_SHADER:
                return ".frag.cached";
            case GL_GEOMETRY_SHADER:
                return ".geom.cached";
            case GL_COMPUTE_SHADER:
                return ".comp.cached";
            case GL_TESS_CONTROL_SHADER:
                return ".tessc.cached";
            case GL_TESS_EVALUATION_SHADER:
                return ".tesse.cached";
            case GL_NONE:
                return ".none.cached";
        }

        PT_ASSERT(false, "Unknown shader type");
        return "";
    }

    static constexpr shaderc_shader_kind OpenGlShaderToSpriv(GLenum glShader)
    {
        switch (glShader)
        {
            case GL_VERTEX_SHADER:
                return shaderc_glsl_vertex_shader;
            case GL_FRAGMENT_SHADER:
                return shaderc_glsl_fragment_shader;
            case GL_GEOMETRY_SHADER:
                return shaderc_glsl_geometry_shader;
            case GL_COMPUTE_SHADER:
                return shaderc_glsl_compute_shader;
            case GL_TESS_CONTROL_SHADER:
                return shaderc_glsl_tess_control_shader;
            case GL_TESS_EVALUATION_SHADER:
                return shaderc_glsl_tess_evaluation_shader;
            case GL_NONE:
                return shaderc_glsl_infer_from_source;
        }

        PT_ASSERT(false, "Unknown shader type");
        return shaderc_glsl_infer_from_source;
    }

    static constexpr GLenum SpriVShaderTypeToOpenGL(shaderc_shader_kind type)
    {
        switch (type)
        {
            case shaderc_glsl_vertex_shader:
                return GL_VERTEX_SHADER;
            case shaderc_glsl_fragment_shader:
                return GL_FRAGMENT_SHADER;
            case shaderc_glsl_geometry_shader:
                return GL_GEOMETRY_SHADER;
            case shaderc_glsl_compute_shader:
                return GL_COMPUTE_SHADER;
            case shaderc_glsl_tess_control_shader:
                return GL_TESS_CONTROL_SHADER;
            case shaderc_glsl_tess_evaluation_shader:
                return GL_TESS_EVALUATION_SHADER;
            case shaderc_glsl_infer_from_source:
                return GL_NONE;
        }

        PT_ASSERT(false, "Unknown shader type");
        return GL_NONE;
    }

    static constexpr const char* OpenGLShaderTypeToString(GLenum type)
    {
        switch (type) {
            case GL_VERTEX_SHADER:
                return "Vertex";
            case GL_FRAGMENT_SHADER:
                return "Fragment";
            case GL_GEOMETRY_SHADER:
                return "Geometry";
            case GL_COMPUTE_SHADER:
                return "Compute";
            case GL_TESS_CONTROL_SHADER:
                return "Tessellation Control";
            case GL_TESS_EVALUATION_SHADER:
                return "Tessellation Evaluation";
            case GL_NONE:
                return "None";
        }
        return "None";
    }

    OpenGLShader::OpenGLShader(const String &filepath)
    {
        auto fileName = std::filesystem::path((std::string)filepath).filename().string();
        auto name = fileName.substr(0, fileName.find_last_of('.'));
        m_Name = name;

        std::ifstream file(filepath.Get());
        PT_ASSERT(file.is_open(), "Failed to open file: {}", filepath);
        std::stringstream ss;
        ss << file.rdbuf();
        file.close();
        String source = ss.str();
        PT_LOG_INFO("Compiling shader: {}", source);
        auto shaderSources = PreProcess(source);

        Handle(shaderSources);
    }

    OpenGLShader::OpenGLShader(const String &filepath, const String& name)
    {
        m_Name = name;

        String source = FileUtils::ReadFile(filepath);
        auto shaderSources = PreProcess(source);

        Handle(shaderSources);
    }

    OpenGLShader::OpenGLShader(const String& name, const std::initializer_list<const String> &src)
    {
        m_Name = name;

        std::vector<Pair<uint32_t, String>> shaderSources;
        for (auto& source : src)
        {
            auto shaderSources1 = PreProcess(source);
            shaderSources.insert(shaderSources.end(), shaderSources1.begin(), shaderSources1.end());
        }

        Handle(shaderSources);
    }

    OpenGLShader::~OpenGLShader()
    {

    }

    std::vector<Pair<uint32_t, String>> OpenGLShader::PreProcess(const String &source)
    {
        std::vector<Pair<uint32_t, String>> shaderSources;

        const char* typeToken = "#type";

        std::stringstream stream(source);

        std::string _line;

        while (std::getline(stream, _line))
        {
            String line = _line;
            if (line.Contains(typeToken))
            {
                String type = line.Substring(line.Find(typeToken) + strlen(typeToken) + 1);
                if (type.Contains("vertex"))
                {
                    Pair<uint32_t, String> pair;
                    pair.first = GL_VERTEX_SHADER;
                    pair.second = "\n";
                    shaderSources.push_back(pair);
                }
                else if (type.Contains("fragment"))
                {
                    Pair<uint32_t, String> pair;
                    pair.first = GL_FRAGMENT_SHADER;
                    pair.second = "\n";
                    shaderSources.push_back(pair);
                }
                else if (type.Contains("geometry"))
                {
                    Pair<uint32_t, String> pair;
                    pair.first = GL_GEOMETRY_SHADER;
                    pair.second = "\n";
                    shaderSources.push_back(pair);
                }
                else if (type.Contains("compute"))
                {
                    Pair<uint32_t, String> pair;
                    pair.first = GL_COMPUTE_SHADER;
                    pair.second = "\n";
                    shaderSources.push_back(pair);
                }
                else if (type.Contains("tessellation"))
                {
                    Pair<uint32_t, String> pair;
                    pair.first = GL_TESS_CONTROL_SHADER;
                    pair.second = "\n";
                    shaderSources.push_back(pair);
                    Pair<uint32_t, String> pair2;
                    pair2.first = GL_TESS_EVALUATION_SHADER;
                    pair2.second = "\n";
                    shaderSources.push_back(pair2);
                }
                else if (type.Contains("tessellation_control"))
                {
                    Pair<uint32_t, String> pair;
                    pair.first = GL_TESS_CONTROL_SHADER;
                    pair.second = "\n";
                    shaderSources.push_back(pair);
                }
                else if (type.Contains("tessellation_evaluation"))
                {
                    Pair<uint32_t, String> pair;
                    pair.first = GL_TESS_EVALUATION_SHADER;
                    pair.second = "\n";
                    shaderSources.push_back(pair);
                }
                else
                {
                    PT_ASSERT(false, "Unknown shader type!");
                    break;
                }
            }
            else
            {
                //PT_ASSERT(!shaderSources.empty(), "No shader type defined!");
                if (!shaderSources.empty())
                    shaderSources.back().second += line + "\n";
            }
        }

        for (auto& shaderSource : shaderSources)
        {
            PT_LOG_INFO("Found Shader type: {}", OpenGLShaderTypeToString(shaderSource.first));
            PT_LOG_INFO("Found Shader source: {}", shaderSource.second);
        }

        return shaderSources;
    }

    void OpenGLShader::Handle(const std::vector<Pair<uint32_t, String>> &shaderSources)
    {
        PT_LOG_INFO("Compiling shader: {0}", m_Name);

        for (auto& shader : shaderSources)
        {
            Compile(shader);
        }

        Link();
    }

    void OpenGLShader::Compile(const Pair<uint32_t, String> &shader)
    {
        PT_LOG_INFO("Compiling shader: {0}", m_Name);
        PT_LOG_INFO("Compiling shader type: {0}", OpenGLShaderTypeToString(shader.first));
        PT_LOG_INFO("Compiling shader source: {0}", shader.second);

        const char* cachePath = GetCachePath();

        if (!std::filesystem::exists(cachePath))
        {
            std::filesystem::create_directories(cachePath);
        }

        static shaderc::Compiler compiler;
        static shaderc::CompileOptions vulkanOptions;
        vulkanOptions.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_3);
        vulkanOptions.SetOptimizationLevel(shaderc_optimization_level_performance);

        std::filesystem::path spirVPath = std::filesystem::path(cachePath) / (std::string(m_Name.Get()) + ".vulk" + GetCacheShaderExtension(shader.first));
        std::filesystem::path openGLPath = std::filesystem::path(cachePath) / (std::string(m_Name.Get()) + ".opgl" + GetCacheShaderExtension(shader.first));

        PT_LOG_INFO("Gettet {}", shader.second.Get()); // raw string is fucked
        shaderc::SpvCompilationResult result = compiler.CompileGlslToSpv(shader.second.Get(), OpenGlShaderToSpriv(shader.first), m_Name.Get(), vulkanOptions);
        if (result.GetCompilationStatus() != shaderc_compilation_status_success)
        {
            PT_ASSERT(false, "Failed to compile shader: {} error: {}", m_Name, result.GetErrorMessage());
            PT_LOG_ERROR("Failed to compile shader: {} error: {}", m_Name, result.GetErrorMessage());
            return;
        }

        std::vector<uint32_t> spirv = { result.cbegin(), result.cend() };
        m_SpirV.push_back({ shader.first, spirv });

        std::ofstream file1(spirVPath, std::ios::binary);
        if (file1.is_open())
        {
            file1.write((char*)spirv.data(), spirv.size() * sizeof(uint32_t));
            file1.flush();
            file1.close();
        }
        else
        {
            PT_ASSERT(false, "Failed to open file: {}", spirVPath.string());
            PT_LOG_ERROR("Failed to open file: {}", spirVPath.string());
            return;
        }

        static shaderc::CompileOptions openGLOptions;
        openGLOptions.SetTargetEnvironment(shaderc_target_env_opengl, shaderc_env_version_opengl_4_5);
        openGLOptions.SetOptimizationLevel(shaderc_optimization_level_performance);

        static spirv_cross::CompilerGLSL glslCompiler(spirv);
        Pair<uint32_t, String> glsl = { shader.first, glslCompiler.compile() };

        result = compiler.CompileGlslToSpv(glsl.second.Get(), OpenGlShaderToSpriv(shader.first), openGLPath.string().c_str(), openGLOptions);
        if (result.GetCompilationStatus() != shaderc_compilation_status_success)
        {
            PT_ASSERT(false, "Failed to compile shader: {} error: {}", m_Name, result.GetErrorMessage());
            PT_LOG_ERROR("Failed to compile shader: {} error: {}", m_Name, result.GetErrorMessage());
            return;
        }

        std::vector<uint32_t> openGLSpirV = { result.cbegin(), result.cend() };
        m_OpenGLSpirV.push_back({ shader.first, openGLSpirV });

        std::ofstream file2(openGLPath, std::ios::binary);
        if (file2.is_open())
        {
            file2.write((char*)openGLSpirV.data(), openGLSpirV.size() * sizeof(uint32_t));
            file2.flush();
            file2.close();
        }
        else
        {
            PT_ASSERT(false, "Failed to open file: {}", openGLPath.string());
            PT_LOG_ERROR("Failed to open file: {}", openGLPath.string());
        }
    }

    void OpenGLShader::Link()
    {
        RendererID rendererId = glCreateProgram();

        std::vector<GLuint> shaderIds;
        for (auto&&[type, spirv] : m_OpenGLSpirV)
        {
            GLuint shaderId = glCreateShader(type);
            glShaderBinary(1, &shaderId, GL_SHADER_BINARY_FORMAT_SPIR_V, spirv.data(), spirv.size() * sizeof(uint32_t));
            glSpecializeShader(shaderId, "main", 0, nullptr, nullptr);
            glAttachShader(rendererId, shaderId);
            shaderIds.push_back(shaderId);
        }

        glLinkProgram(rendererId);

        GLint isLinked = 0;
        glGetProgramiv(rendererId, GL_LINK_STATUS, (int*)&isLinked);

        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(rendererId, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(rendererId, maxLength, nullptr, infoLog.data());

            glDeleteProgram(rendererId);

            for (auto id : shaderIds)
                glDeleteShader(id);

            if (infoLog.size() > 0)
            {
                PT_ASSERT(false, "Shader link failure: {}", infoLog.data());
                PT_LOG_ERROR("Shader link failure: {}", infoLog.data());
            }
            else
            {
                PT_ASSERT(false, "Shader link failure");
                PT_LOG_ERROR("Shader link failure");
            }
            return;
        }

        for (auto id : shaderIds)
        {
            glDetachShader(rendererId, id);
            glDeleteShader(id);
        }

        m_RendererID = rendererId;
    }

    void OpenGLShader::Bind() const
    {
        glUseProgram(m_RendererID);
    }

    void *OpenGLShader::GetRenderObject() const
    {
        return (void*)&m_RendererID;
    }
}