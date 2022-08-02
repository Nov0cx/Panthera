#ifndef PANTHERA_OPENGLSHADER_HPP
#define PANTHERA_OPENGLSHADER_HPP

#include "Panthera/Render/Shader.hpp"
#include "Panthera/Core/Pointer.hpp"
#include <string>
#include "Panthera/Render/RenderAPI.hpp"

namespace Panthera
{
    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string &vertexSrc, const std::string &fragmentSrc);
        OpenGLShader(const std::string &path);

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual RendererID GetRendererID() const override;

    private:
        RendererID m_RendererID;
    };
}

#endif //PANTHERA_OPENGLSHADER_HPP
