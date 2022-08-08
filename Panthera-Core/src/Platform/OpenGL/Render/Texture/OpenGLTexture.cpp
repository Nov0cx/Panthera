#include "OpenGLTexture.hpp"

#include <glad/glad.h>
#include "Panthera/Core/Log.hpp"
#include "Vendor/stb/stb_image.h"

namespace Panthera
{

    OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
    {
        m_Width = width;
        m_Height = height;

        m_Format = GL_RGBA8;
        m_DataFormat = GL_RGBA;

        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        glTextureStorage2D(m_RendererID, 1, m_Format, m_Width, m_Height);

        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

        m_IsLoaded = true;
    }

    OpenGLTexture2D::OpenGLTexture2D(const std::string &path)
    {
        m_IsLoaded = false;
        stbi_set_flip_vertically_on_load(true);
        int width, height, nrChannels;
        unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

        ASSERT(data, "Failed to load texture")

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

        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        glTextureStorage2D(m_RendererID, 1, m_Format, m_Width, m_Height);

        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);

        m_IsLoaded = true;
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
}