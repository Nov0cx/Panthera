#include "OpenGLShader.hpp"

#include <glad/glad.h>

namespace Panthera
{

    static constexpr const char* GetCachePath()
    {
        return "./.cache/Shaders/";
    }

    OpenGLShader::OpenGLShader(const String &filepath)
    {
        String source = FileUtils::ReadFile(filepath);
        auto shaderSources = PreProcess(source);

        for (auto& shader : shaderSources)
        {
            Compile(shader);
        }

        Link();
    }

    OpenGLShader::OpenGLShader(const std::initializer_list<const String> &src)
    {

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
                if (type == "vertex")
                {
                    shaderSources.push_back({ GL_VERTEX_SHADER, "\n" });
                }
                else if (type == "fragment")
                {
                    shaderSources.push_back({ GL_FRAGMENT_SHADER, "\n" });
                }
                else if (type == "geometry")
                {
                    shaderSources.push_back({ GL_GEOMETRY_SHADER, "\n" });
                }
                else if (type == "compute")
                {
                    shaderSources.push_back({ GL_COMPUTE_SHADER, "\n" });
                }
                else if (type == "tessellation")
                {
                    shaderSources.push_back({ GL_TESS_CONTROL_SHADER, "\n" });
                    shaderSources.push_back({ GL_TESS_EVALUATION_SHADER, "\n" });
                }
                else if (type == "tessellation_control")
                {
                    shaderSources.push_back({ GL_TESS_CONTROL_SHADER, "\n" });
                }
                else if (type == "tessellation_evaluation")
                {
                    shaderSources.push_back({ GL_TESS_EVALUATION_SHADER, "\n" });
                }
                else
                {
                    PT_ASSERT(false, "Unknown shader type!");
                    break;
                }
            }
            else
            {
                shaderSources.back().second += line + "\n";
            }
        }

        return shaderSources;
    }

    void OpenGLShader::Compile(const Pair<uint32_t, String> &shader)
    {
        const char* cachePath = GetCachePath();

        if (!std::filesystem::exists(cachePath))
        {
            std::filesystem::create_directories(cachePath);
        }


    }

    void OpenGLShader::Link()
    {

    }
}