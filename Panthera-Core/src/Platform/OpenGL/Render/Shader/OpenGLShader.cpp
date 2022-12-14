#include "OpenGLShader.hpp"

#include <shaderc/shaderc.hpp>
#include <spirv_cross/spirv_cross.hpp>
#include <spirv_cross/spirv_glsl.hpp>
#include <glad/glad.h>

#include "Panthera/Core/Log.hpp"
#include "Panthera/Render/RenderAPI.hpp"
#include "Panthera/Core/Application.hpp"

#include <vector>
#include <filesystem>
#include <sstream>
#include <fstream>
#include <string>
#include <unordered_map>

namespace Panthera
{

    static const char *HASH_CACHE_FILE_NAME = "shader_cache.txt";

    struct HashGroup
    {
        std::unordered_map <std::string, uint64_t> HashMap;



        void Load()
        {
            std::ifstream file(HASH_CACHE_FILE_NAME);
            if (file.is_open())
            {
                std::string line;
                while (std::getline(file, line))
                {
                    std::stringstream ss(line);
                    std::string key;
                    uint64_t value;
                    ss >> key >> value;
                    HashMap[key] = value;
                }
                file.close();
            }
        }

        void Save()
        {
            std::ofstream file(HASH_CACHE_FILE_NAME);
            if (file.is_open())
            {
                for (auto&[key, value]: HashMap)
                {
                    file << key << " " << value << std::endl;
                }
                file.close();
            }
        }

        bool HasHash(const std::string &name)
        {
            return HashMap.find(name) != HashMap.end();
        }

        uint64_t GetHash(const std::string &name)
        {
            return HashMap[name];
        }

        uint64_t InsertHash(const std::string &name, uint64_t hash)
        {
            HashMap[name] = hash;
            return hash;
        }

        bool IsUpToDate(const std::string &name, const std::string &src)
        {
            if (!HasHash(name))
            {
                return false;
            }

            uint64_t hash = GetHash(name);
            uint64_t newHash = std::hash < std::string > {}(src);

            return hash == newHash;
        }

        static uint64_t CreateHash(const std::string &src)
        {
            return std::hash < std::string > {}(src);
        }
    };

    static const char *GLShaderTypeToString(GLenum type)
    {
        switch (type)
        {
            case GL_VERTEX_SHADER:
                return "GL_VERTEX_SHADER";
            case GL_FRAGMENT_SHADER:
                return "GL_FRAGMENT_SHADER";
            case GL_GEOMETRY_SHADER:
                return "GL_GEOMETRY_SHADER";
            case GL_TESS_CONTROL_SHADER:
                return "GL_TESS_CONTROL_SHADER";
            case GL_TESS_EVALUATION_SHADER:
                return "GL_TESS_EVALUATION_SHADER";
            case GL_COMPUTE_SHADER:
                return "GL_COMPUTE_SHADER";
            default:
                return "Unknown";
        }
    }

    static const char *GetShaderCache()
    {
        return "cache/opengl/shader";
    }

    static void CreateCache()
    {
        std::filesystem::path cachePath = GetShaderCache();
        if (!std::filesystem::exists(cachePath))
        {
            std::filesystem::create_directories(cachePath);
        }
    }

    struct ShaderSrc
    {
        std::string src;
        GLenum type;
    };

    static const char *GetCachedShaderExtension(GLenum type)
    {
        switch (type)
        {
            case GL_VERTEX_SHADER:
                return ".cached.vert";
            case GL_FRAGMENT_SHADER:
                return ".cached.frag";
            case GL_GEOMETRY_SHADER:
                return ".cached.geom";
            case GL_TESS_CONTROL_SHADER:
                return ".cached.tesc";
            case GL_TESS_EVALUATION_SHADER:
                return ".cached.tese";
            case GL_COMPUTE_SHADER:
                return ".cached.comp";
            default:
                ASSERT(false, "Unknown Shader Type! {}", (int) type)
        }
    }

    static shaderc_shader_kind GLShaderTypeToShaderC(GLenum type)
    {
        switch (type)
        {
            case GL_VERTEX_SHADER:
                return shaderc_glsl_vertex_shader;
            case GL_FRAGMENT_SHADER:
                return shaderc_glsl_fragment_shader;
            case GL_GEOMETRY_SHADER:
                return shaderc_glsl_geometry_shader;
            case GL_TESS_CONTROL_SHADER:
                return shaderc_glsl_tess_control_shader;
            case GL_TESS_EVALUATION_SHADER:
                return shaderc_glsl_tess_evaluation_shader;
            case GL_COMPUTE_SHADER:
                return shaderc_glsl_compute_shader;
            default:
                ASSERT(false, "Unknown Shader Type! {}", (int) type)
        }
        ASSERT(false, "Unknown Shader Stage! {}", (int) type)
    }


    OpenGLShader::OpenGLShader(const std::string &name, const std::string &vertexSrc, const std::string &fragmentSrc)
            : m_Name(std::move(name))
    {
        LOG_DEBUG("Compiling Shader: {}", m_Name)
        CreateCache();

        std::vector <ShaderSrc> srcs = {};

        srcs.push_back({vertexSrc, GL_VERTEX_SHADER});
        srcs.push_back({fragmentSrc, GL_FRAGMENT_SHADER});

        CompileVulkanShader(srcs);

        CompileShader();

        CreateProgram();
    }

    std::vector <ShaderSrc> GetShaders(const std::string &src)
    {
        std::vector <ShaderSrc> srcs = {};
        std::stringstream stream(src);
        std::stringstream currentShader;
        GLenum currentType = GL_NONE;

        std::string line;

        while (std::getline(stream, line))
        {
            std::string lower = line;
            std::transform(lower.begin(), lower.end(), lower.begin(),
                           [](unsigned char c)
                           { return std::tolower(c); });

            if (lower.find("vertex") != std::string::npos && lower.find("shader") != std::string::npos)
            {
                if (currentType != GL_NONE)
                {
                    srcs.push_back({currentShader.str(), currentType});
                    currentShader.str("");
                }
                currentType = GL_VERTEX_SHADER;

                currentShader << line << "\n";
            } else if ((lower.find("fragment") != std::string::npos && lower.find("shader") != std::string::npos) ||
                       (lower.find("pixel") != std::string::npos && lower.find("shader") != std::string::npos))
            {
                if (currentType != GL_NONE)
                {
                    srcs.push_back({currentShader.str(), currentType});
                    currentShader.str("");
                }
                currentType = GL_FRAGMENT_SHADER;
                currentShader << line << "\n";
            } else if (lower.find("geometry") != std::string::npos && lower.find("shader") != std::string::npos)
            {
                if (currentType != GL_NONE)
                {
                    srcs.push_back({currentShader.str(), currentType});
                    currentShader.str("");
                }
                currentType = GL_GEOMETRY_SHADER;
                currentShader << line << "\n";
            } else if (lower.find("tess control") != std::string::npos && lower.find("shader") != std::string::npos)
            {
                if (currentType != GL_NONE)
                {
                    srcs.push_back({currentShader.str(), currentType});
                    currentShader.str("");
                }
                currentType = GL_TESS_CONTROL_SHADER;
                currentShader << line << "\n";
            } else if (lower.find("tess evaluation") != std::string::npos && lower.find("shader") != std::string::npos)
            {
                if (currentType != GL_NONE)
                {
                    srcs.push_back({currentShader.str(), currentType});
                    currentShader.str("");
                }
                currentType = GL_TESS_EVALUATION_SHADER;
                currentShader << line << "\n";
            } else if (lower.find("compute") != std::string::npos && lower.find("shader") != std::string::npos)
            {
                if (currentType != GL_NONE)
                {
                    srcs.push_back({currentShader.str(), currentType});
                    currentShader.str("");
                }
                currentType = GL_COMPUTE_SHADER;
                currentShader << line << "\n";
            } else
            {
                currentShader << line << "\n";
            }
        }

        if (currentType != GL_NONE)
        {
            srcs.push_back({currentShader.str(), currentType});
        }

        return srcs;
    }

    std::vector<GLenum> GetShaderTypes(const std::string &src)
    {
        std::vector<GLenum> types = {};

        std::stringstream ss(src);
        std::string line;

        while (std::getline(ss, line))
        {
            std::string lower = line;
            std::transform(lower.begin(), lower.end(), lower.begin(),
                           [](unsigned char c)
                           { return std::tolower(c); });

            if (lower.find("vertex") != std::string::npos && lower.find("shader") != std::string::npos)
            {
                types.push_back(GL_VERTEX_SHADER);
            } else if ((lower.find("fragment") != std::string::npos && lower.find("shader") != std::string::npos) ||
                       (lower.find("pixel") != std::string::npos && lower.find("shader") != std::string::npos))
            {
                types.push_back(GL_FRAGMENT_SHADER);
            } else if (lower.find("geometry") != std::string::npos && lower.find("shader") != std::string::npos)
            {
                types.push_back(GL_GEOMETRY_SHADER);
            } else if (lower.find("tess control") != std::string::npos && lower.find("shader") != std::string::npos)
            {
                types.push_back(GL_TESS_CONTROL_SHADER);
            } else if (lower.find("tess evaluation") != std::string::npos && lower.find("shader") != std::string::npos)
            {
                types.push_back(GL_TESS_EVALUATION_SHADER);
            } else if (lower.find("compute") != std::string::npos && lower.find("shader") != std::string::npos)
            {
                types.push_back(GL_COMPUTE_SHADER);
            }
        }

        return types;
    }

    OpenGLShader::OpenGLShader(const std::string &path)
    {
        std::filesystem::path filePath = path;
        m_Name = filePath.filename().string();

        LOG_DEBUG("Compiling Shader: {}, path: {}", m_Name, path)

        CreateCache();

        std::ifstream file(filePath, std::ios::in | std::ios::binary);
        ASSERT(file.is_open(), "Failed to open file: {}", filePath.string())

        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();
        std::string src = buffer.str();

        HashGroup hashGroup;
        hashGroup.Load();

        if (hashGroup.IsUpToDate(filePath.string(), src))
        {
            LOG_DEBUG("Shader is up to date, loading from cache")
            auto shader = GetShaderTypes(src);
            for (auto type : shader)
            {
                LOG_DEBUG("Loading shader: {}, type: {}", m_Name, GLShaderTypeToString(type))
                LoadShader(filePath.string(), type, src);
            }
            CreateProgram();
            hashGroup.Save();
            return;
        } else
        {
            LOG_DEBUG("Shader is out of date, recompiling")
        }

        auto srcs = GetShaders(src);

        CompileVulkanShader(srcs);
        CompileShader();
        CreateProgram();

        hashGroup.InsertHash(filePath.string(), HashGroup::CreateHash(src));
        hashGroup.Save();
    }

    void OpenGLShader::Bind() const
    {
        glUseProgram(m_RendererID);
    }

    void OpenGLShader::Unbind() const
    {
        glUseProgram(0);
    }

    RendererID OpenGLShader::GetRendererID() const
    {
        return m_RendererID;
    }

    void OpenGLShader::CompileVulkanShader(std::vector <ShaderSrc> &srcs)
    {
        std::filesystem::path cachePath = GetShaderCache();

        shaderc::Compiler compiler;
        shaderc::CompileOptions options;
        options.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_2);
        options.SetOptimizationLevel(shaderc_optimization_level_performance);

        m_VulkanBinary.clear();

        for (auto &src: srcs)
        {
            std::filesystem::path cachedFilePath = cachePath / (m_Name + ".vulk" + GetCachedShaderExtension(src.type));

            shaderc::SpvCompilationResult result = compiler.CompileGlslToSpv(src.src.c_str(),
                                                                             GLShaderTypeToShaderC(src.type),
                                                                             m_Name.c_str(), options);
            if (result.GetCompilationStatus() != shaderc_compilation_status_success)
            {
                LOG_ERROR("Failed to compile shader: {}, error: {}", m_Name, result.GetErrorMessage())
                ASSERT(false, "Failed to compile shader: {}, error: {}", m_Name, result.GetErrorMessage())
            }

            m_VulkanBinary[src.type] = std::vector<uint32_t>(result.cbegin(), result.cend());

            std::ofstream out(cachedFilePath, std::ios::binary | std::ios::out);
            if (out.is_open())
            {
                auto &binary = m_VulkanBinary[src.type];
                out.write(reinterpret_cast<char *>(binary.data()), binary.size() * sizeof(uint32_t));
                out.flush();
                out.close();
            } else
            {
                ASSERT(false, "Failed to open file: '{}'. Cannot create shader '{}'", cachedFilePath.string(),
                       m_Name)
            }

        }
    }

    void OpenGLShader::CompileShader()
    {
        shaderc::Compiler compiler;
        shaderc::CompileOptions options;
        options.SetTargetEnvironment(shaderc_target_env_opengl, shaderc_env_version_opengl_4_5);
        options.SetOptimizationLevel(shaderc_optimization_level_performance);

        std::filesystem::path cachePath = GetShaderCache();

        m_OpenGLBinary.clear();

        for (auto&&[type, spirvBinary]: m_VulkanBinary)
        {
            std::filesystem::path cachedFilePath = cachePath / (m_Name + GetCachedShaderExtension(type));

            spirv_cross::CompilerGLSL glslCompiler(spirvBinary);
            m_OpenGLSrc[type] = glslCompiler.compile();

            shaderc::SpvCompilationResult result = compiler.CompileGlslToSpv(m_OpenGLSrc[type].c_str(),
                                                                             GLShaderTypeToShaderC(type),
                                                                             m_Name.c_str(), options);
            ASSERT(result.GetCompilationStatus() == shaderc_compilation_status_success,
                   "Failed to compile shader: {}", result.GetErrorMessage())

            m_OpenGLBinary[type] = std::vector<uint32_t>(result.cbegin(), result.cend());

            std::ofstream out(cachedFilePath, std::ios::binary | std::ios::out);
            if (out.is_open())
            {
                auto &binary = m_OpenGLBinary[type];
                out.write(reinterpret_cast<char *>(binary.data()), binary.size() * sizeof(uint32_t));
                out.flush();
                out.close();
            } else
            {
                ASSERT(false, "Failed to open file: '{}'. Cannot create shader '{}'", cachedFilePath.string(),
                       m_Name)
            }

        }
    }


    void OpenGLShader::CreateProgram()
    {
        RendererID program = glCreateProgram();

        std::vector <GLuint> shaders;
        for (auto&&[type, binary]: m_OpenGLBinary)
        {
            GLuint shader = shaders.emplace_back(glCreateShader(type));
            glShaderBinary(1, &shader, GL_SHADER_BINARY_FORMAT_SPIR_V, binary.data(), binary.size() * sizeof(uint32_t));
            glSpecializeShader(shader, "main", 0, nullptr, nullptr);
            glAttachShader(program, shader);
        }

        glLinkProgram(program);

        GLint linkSuccess = 0;
        glGetProgramiv(program, GL_LINK_STATUS, &linkSuccess);
        if (linkSuccess == GL_FALSE)
        {
            GLint infoLogLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
            std::vector <GLchar> infoLog(infoLogLength);
            glGetProgramInfoLog(program, infoLogLength, nullptr, infoLog.data());

            glDeleteProgram(program);

            for (auto shader: shaders)
            {
                glDeleteShader(shader);
            }
            if (infoLog.size() > 0)
            {
                LOG_ERROR("Failed to link shader: {}, error: {}", m_Name, infoLog.data())
                ASSERT(false, "Failed to link shader: {}, error: {}", m_Name, infoLog.data())
            } else
            {
                LOG_ERROR("Failed to link shader: {}, error: {}", m_Name, "Unknown")
                ASSERT(false, "Failed to link shader: {}, error: {}", m_Name, "Unknown")
            }
        }

        for (auto shader: shaders)
        {
            glDetachShader(program, shader);
            glDeleteShader(shader);
        }

        m_RendererID = program;
    }

    void OpenGLShader::LoadShader(const std::string &path, uint32_t type, const std::string &src)
    {

        std::filesystem::path cachePath = GetShaderCache();
        std::filesystem::path cachedFilePath = cachePath / (m_Name + GetCachedShaderExtension(type));

        std::ifstream in(cachedFilePath, std::ios::binary | std::ios::in);
        if (in.is_open())
        {
            in.seekg(0, std::ios::end);
            auto length = in.tellg();
            in.seekg(0, std::ios::beg);

            auto &binary = m_OpenGLBinary[type];
            binary.resize(length / sizeof(uint32_t));
            in.read(reinterpret_cast<char *>(binary.data()), length);
        }
        else
        {
            LOG_ERROR("Failed to open file: '{}'. Cannot load shader '{}'. Recompiling...", cachedFilePath.string(), m_Name)
            auto srcs = GetShaders(src);
            CompileVulkanShader(srcs);
        }
    }
}