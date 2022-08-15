#include "OpenGLTexture.hpp"

#include <glad/glad.h>
#include "Panthera/Core/Log.hpp"
#include "Vendor/stb/stb_image.h"
#include <cstring>

namespace Panthera
{

    GLenum InternalFormatToOpenGL(Texture2DInternalFormat format)
    {
        switch (format)
        {
            case Texture2DInternalFormat::R8:
                return GL_R8;
            case Texture2DInternalFormat::RG8:
                return GL_RG8;
            case Texture2DInternalFormat::RGB8:
                return GL_RGB8;
            case Texture2DInternalFormat::RGBA8:
                return GL_RGBA8;
            default:
                ASSERT(false, "Unknown Texture2DInternalFormat");
        }
    }

    GLenum DataFormatToOpenGL(Texture2DDataFormat format)
    {
        switch (format)
        {
            case Texture2DDataFormat::Red:
                return GL_RED;
            case Texture2DDataFormat::RG:
                return GL_RG;
            case Texture2DDataFormat::RGB:
                return GL_RGB;
            case Texture2DDataFormat::RGBA:
                return GL_RGBA;
            default:
                ASSERT(false, "Unknown Texture2DDataFormat");
        }
    }

    GLenum FilterToOpenGL(Texture2DFilter filter)
    {
        switch (filter)
        {
            case Texture2DFilter::Nearest:
                return GL_NEAREST;
            case Texture2DFilter::Linear:
                return GL_LINEAR;
            default:
                ASSERT(false, "Unknown Texture2DFilter");
        }
    }

    GLenum WrappingToOpenGL(Texture2DWrapping wrapping)
    {
        switch (wrapping)
        {
            case Texture2DWrapping::ClampToEdge:
                return GL_CLAMP_TO_EDGE;
            case Texture2DWrapping::Repeat:
                return GL_REPEAT;
            default:
                ASSERT(false, "Unknown Texture2DWrapping");
        }
    }

    OpenGLTexture2D::OpenGLTexture2D(const Texture2DSpecification& spec)
    {
        if (strcmp(spec.Path, "") == 0)
        {
            m_Width = spec.Width;
            m_Height = spec.Height;

            m_Format = InternalFormatToOpenGL(spec.InternalFormat);
            m_DataFormat = DataFormatToOpenGL(spec.DataFormat);

            glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
            glTextureStorage2D(m_RendererID, 1, m_Format, m_Width, m_Height);

            glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, FilterToOpenGL(spec.Filter));
            glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, FilterToOpenGL(spec.Filter));

            glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, WrappingToOpenGL(spec.Wrapping));
            glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_R, WrappingToOpenGL(spec.Wrapping));
            glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, WrappingToOpenGL(spec.Wrapping));

            m_IsLoaded = true;

        }
        else
        {
            m_IsLoaded = false;
            stbi_set_flip_vertically_on_load(true);
            int width, height, nrChannels;
            unsigned char *data = stbi_load(spec.Path, &width, &height, &nrChannels, 0);

            ASSERT(data, "Failed to load texture: '{}'", spec.Path);

            m_Width = width;
            m_Height = height;

            switch (nrChannels)
            {
                case 1:
                    m_Format = GL_R8;
                    m_DataFormat = GL_RED;
                    break;
                case 2:
                    m_Format = GL_RG8;
                    m_DataFormat = GL_RG;
                    break;
                case 3:
                    m_Format = GL_RGB8;
                    m_DataFormat = GL_RGB;
                    break;
                case 4:
                    m_Format = GL_RGBA8;
                    m_DataFormat = GL_RGBA;
                    break;
                default:
                    ASSERT(false, "Unsupported texture format")
            }

            if (m_Format != InternalFormatToOpenGL(spec.InternalFormat))
            {
                LOG_WARN("The loaded texture '{}' has not the same format as the format given in the specification.", spec.Path)
            }
            if (m_DataFormat != DataFormatToOpenGL(spec.DataFormat))
            {
                LOG_WARN("The loaded texture '{}' has not the same data format as the data format given in the specification.", spec.Path)
            }

            glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
            glTextureStorage2D(m_RendererID, 1, m_Format, m_Width, m_Height);

            glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, FilterToOpenGL(spec.Filter));
            glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, FilterToOpenGL(spec.Filter));

            glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_R, WrappingToOpenGL(spec.Wrapping));
            glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, WrappingToOpenGL(spec.Wrapping));
            glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, WrappingToOpenGL(spec.Wrapping));

            glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);

            stbi_image_free(data);

            m_IsLoaded = true;
        }
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &m_RendererID);
    }

    void OpenGLTexture2D::Bind(uint32_t slot)
    {
        glBindTextureUnit(slot, m_RendererID);
        m_CurrentSlot = slot;
    }

    void OpenGLTexture2D::Unbind()
    {
        glBindTextureUnit(m_CurrentSlot, 0);
    }

    void OpenGLTexture2D::SetData(void *data, uint32_t size)
    {
        uint32_t bpp = 0;
        switch (m_DataFormat)
        {
            case GL_RED:
                bpp = 1;
                break;
            case GL_RG:
                bpp = 2;
                break;
            case GL_RGB:
                bpp = 3;
                break;
            case GL_RGBA:
                bpp = 4;
                break;
            default:
                ASSERT(false, "Unknown Texture2DDataFormat");
        }
        ASSERT(size == m_Width * m_Height * bpp, "Data must be entire texture!")
        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
    }

    uint32_t OpenGLTexture2D::GetWidth() const
    {
        return m_Width;
    }

    uint32_t OpenGLTexture2D::GetHeight() const
    {
        return m_Height;
    }

    RendererID OpenGLTexture2D::GetRendererID() const
    {
        return m_RendererID;
    }

    bool OpenGLTexture2D::IsLoaded() const
    {
        return m_IsLoaded;
    }

    bool OpenGLTexture2D::operator==(const Texture2D &other) const
    {
        return m_RendererID == other.GetRendererID();
    }
}