#include "OpenGLTexture2D.hpp"

#include <glad/glad.h>
#include <stb_image.h>

namespace Panthera
{

    GLenum GetInternalFormat(Texture2DFormat format)
    {
        switch (format)
        {
            case Texture2DFormat::Red:
                return GL_R8;
            case Texture2DFormat::RG:
                return GL_RG8;
            case Texture2DFormat::RGB:
                return GL_RGB8;
            case Texture2DFormat::RGBA:
                return GL_RGBA8;
            case Texture2DFormat::DepthStencil:
                return GL_DEPTH24_STENCIL8;
           case Texture2DFormat::Depth:
                return GL_DEPTH_COMPONENT;
            default:
                PT_ASSERT(false, "Unknown Texture2DFormat");
        }
        return GL_NONE;
    }

    GLenum GetDataFormat(Texture2DFormat format)
    {
        switch (format)
        {
            case Texture2DFormat::Red:
                return GL_RED;
            case Texture2DFormat::RG:
                return GL_RG;
            case Texture2DFormat::RGB:
                return GL_RGB;
            case Texture2DFormat::RGBA:
                return GL_RGBA;
            case Texture2DFormat::DepthStencil:
                return GL_DEPTH_STENCIL;
            case Texture2DFormat::Depth:
                return GL_DEPTH_COMPONENT;
            default:
                PT_ASSERT(false, "Unknown Texture2DFormat");
        }
        return GL_NONE;
    }

    GLenum GetFilter(Texture2DFiltering filter)
    {
        switch (filter)
        {
            case Texture2DFiltering::Nearest:
                return GL_NEAREST;
            case Texture2DFiltering::Linear:
                return GL_LINEAR;
            default:
                PT_ASSERT(false, "Unknown Texture2DFilter");
        }
        return GL_NONE;
    }

    GLenum GetWrapping(Texture2DWrapping wrapping)
    {
        switch (wrapping)
        {
            case Texture2DWrapping::Repeat:
                return GL_REPEAT;
            case Texture2DWrapping::MirroredRepeat:
                return GL_MIRRORED_REPEAT;
            case Texture2DWrapping::ClampToEdge:
                return GL_CLAMP_TO_EDGE;
            case Texture2DWrapping::ClampToBorder:
                return GL_CLAMP_TO_BORDER;
            default:
                PT_ASSERT(false, "Unknown Texture2DWrapping");
        }
        return GL_NONE;
    }

    OpenGLTexture2D::OpenGLTexture2D(const String &path)
    {
        void* data = LoadTexture(path);
        RecreateTexture();

        SetData(data, m_Info.Width * m_Info.Height * m_Info.Channels);

        m_Path = path;
    }

    OpenGLTexture2D::OpenGLTexture2D(const Texture2DInfo &info)
    {
        m_Info = info;
        RecreateTexture();
    }

    void *OpenGLTexture2D::GetRenderObject() const
    {
        return (void*)&m_RendererID;
    }

    Texture2DInfo &OpenGLTexture2D::GetInfo()
    {
        return m_Info;
    }

    const Texture2DInfo &OpenGLTexture2D::GetInfo() const
    {
        return m_Info;
    }

    void OpenGLTexture2D::SetData(void *data, size_t size)
    {
        if (size != m_Info.Width * m_Info.Height * m_Info.Channels)
        {
            PT_LOG_WARNING("Texture2D::SetData: Size of data does not match texture size, size = {0}, texture size = {1}", size, m_Info.Width * m_Info.Height * m_Info.Channels);
        }
        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Info.Width, m_Info.Height, GetDataFormat(m_Info.Format), GL_UNSIGNED_BYTE, data);
    }

    void OpenGLTexture2D::Recreate(const String &path)
    {
        glDeleteTextures(1, &m_RendererID);

        if (path.IsEmpty() && m_Path.IsEmpty())
        {
            if (!path.IsEmpty())
                m_Path = path;

            void* data = LoadTexture(m_Path);
            RecreateTexture();
            SetData(data, m_Info.Width * m_Info.Height * m_Info.Channels);
            return;
        }

        RecreateTexture();
    }

    void OpenGLTexture2D::Clear(int value)
    {
        glClearTexImage(m_RendererID, 0, GetDataFormat(m_Info.Format), GL_UNSIGNED_BYTE, &value);
    }

    void OpenGLTexture2D::Resize(uint32_t width, uint32_t height)
    {
        m_Info.Width = width;
        m_Info.Height = height;
        Recreate();
    }

    bool OpenGLTexture2D::operator==(const Texture2D &other) const
    {
        return m_RendererID == ((OpenGLTexture2D&)other).m_RendererID;
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &m_RendererID);
    }

    void *OpenGLTexture2D::LoadTexture(const String &path)
    {
        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        stbi_uc *data = stbi_load(path.Get(), &width, &height, &channels, 0);
        if (!data)
        {
            PT_LOG_ERROR("Failed to load image: {0}", path);
            return nullptr;
        }

        m_Info.Width = width;
        m_Info.Height = height;
        m_Info.Channels = channels;

        switch (channels)
        {
            case 1:
                m_Info.Format = Texture2DFormat::Red;
                break;
            case 2:
                m_Info.Format = Texture2DFormat::RG;
                break;
            case 3:
                m_Info.Format = Texture2DFormat::RGB;
                break;
            case 4:
                m_Info.Format = Texture2DFormat::RGBA;
                break;
        }

        m_Info.Filtering = Texture2DFiltering::Linear;
        m_Info.Wrapping = Texture2DWrapping::ClampToEdge;

        return data;
    }

    void OpenGLTexture2D::RecreateTexture()
    {
        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        glTextureStorage2D(m_RendererID, 1, GetInternalFormat(m_Info.Format), m_Info.Width, m_Info.Height);

        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GetFilter(m_Info.Filtering));
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GetFilter(m_Info.Filtering));

        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GetWrapping(m_Info.Wrapping));
        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GetWrapping(m_Info.Wrapping));
        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_R, GetWrapping(m_Info.Wrapping));
    }

    void OpenGLTexture2D::SetFiltering(Texture2DFiltering filtering)
    {
        m_Info.Filtering = filtering;
    }

    void OpenGLTexture2D::SetWrapping(Texture2DWrapping wrapping)
    {
        m_Info.Wrapping = wrapping;
    }

    void OpenGLTexture2D::Bind(uint32_t slot) const
    {
        glBindTextureUnit(slot, m_RendererID);
    }
}