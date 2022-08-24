#include "OpenGLFramebuffer.hpp"

#include "Panthera/Core/Log.hpp"
#include "Panthera/Core/Pointer.hpp"
#include "Panthera/Core/Application.hpp"

#include <glad/glad.h>

namespace Panthera
{

    OpenGLFramebuffer::OpenGLFramebuffer(const std::initializer_list <FramebufferAttachmentSpecification> &attachments)
    {
        glCreateFramebuffers(1, &m_RendererID);
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

        for (const auto &attachment: attachments)
        {
            switch (attachment.AttachmentType)
            {
                case FramebufferAttachmentType::Color:
                {
                    Ref<Texture2D> tex = CreateTextureAttachment(attachment);
                    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + m_ColorAttachments.size(), GL_TEXTURE_2D, tex->GetRendererID(), 0);
                    m_ColorAttachments.push_back({attachment.AttachmentType, tex});
                    break;
                }
                case FramebufferAttachmentType::Depth:
                {
                    Ref<Texture2D> tex = CreateDepthBufferAttachment(attachment);
                    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, tex->GetRendererID(), 0);
                    m_DepthAttachment = {attachment.AttachmentType, tex};
                    break;
                }
            }
        }
    }

    OpenGLFramebuffer::~OpenGLFramebuffer()
    {
        glDeleteFramebuffers(1, &m_RendererID);
    }

    void OpenGLFramebuffer::AddAttachment(const FramebufferAttachmentSpecification &attachment)
    {
        switch (attachment.AttachmentType)
        {
            case FramebufferAttachmentType::Color:
            {
                Ref<Texture2D> tex = CreateTextureAttachment(attachment);
                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + m_ColorAttachments.size(), GL_TEXTURE_2D, tex->GetRendererID(), 0);
                m_ColorAttachments.push_back({attachment.AttachmentType, tex});
                break;
            }
            case FramebufferAttachmentType::Depth:
            {
                Ref<Texture2D> tex = CreateDepthBufferAttachment(attachment);
                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, tex->GetRendererID(), 0);
                m_DepthAttachment = {attachment.AttachmentType, tex};
                break;
            }
        }
    }

    void
    OpenGLFramebuffer::AddAttachments(const std::initializer_list <FramebufferAttachmentSpecification> &attachments)
    {
        for (const auto &attachment: attachments)
        {
            switch (attachment.AttachmentType)
            {
                case FramebufferAttachmentType::Color:
                {
                    Ref<Texture2D> tex = CreateTextureAttachment(attachment);
                    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + m_ColorAttachments.size(), GL_TEXTURE_2D, tex->GetRendererID(), 0);
                    m_ColorAttachments.push_back({attachment.AttachmentType, tex, attachment.ClearValue, tex->GetWidth(), tex->GetHeight()});
                    break;
                }
                case FramebufferAttachmentType::Depth:
                {
                    Ref<Texture2D> tex = CreateDepthBufferAttachment(attachment);
                    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, tex->GetRendererID(), 0);
                    m_DepthAttachment = {attachment.AttachmentType, tex, attachment.ClearValue, tex->GetWidth(), tex->GetHeight()};
                    break;
                }
            }
        }
    }

    FramebufferAttachment &OpenGLFramebuffer::GetColorAttachment(uint32_t index)
    {
        return m_ColorAttachments[index];
    }

    std::vector <FramebufferAttachment> &OpenGLFramebuffer::GetColorAttachments()
    {
        return m_ColorAttachments;
    }

    Ref <std::vector<FramebufferAttachment>> OpenGLFramebuffer::GetAttachments(FramebufferAttachmentType type)
    {
        Ref <std::vector<FramebufferAttachment>> attachments = CreateRef<std::vector<FramebufferAttachment>>();
        for (auto &attachment: m_ColorAttachments)
        {
            if (attachment.AttachmentType == type)
            {
                attachments->push_back(attachment);
            }
        }
        return attachments;
    }

    Ref<std::vector<FramebufferAttachment>> OpenGLFramebuffer::GetAttachments(const std::initializer_list<FramebufferAttachmentType>& types)
    {
        Ref<std::vector<FramebufferAttachment>> attachments = CreateRef<std::vector<FramebufferAttachment>>();
        for (auto &attachment: m_ColorAttachments)
        {
            for (auto &type: types)
            {
                if (attachment.AttachmentType == type)
                {
                    attachments->push_back(attachment);
                    break;
                }
            }
        }
        return attachments;
    }

    FramebufferAttachment &OpenGLFramebuffer::GetDepthAttachment()
    {
        return m_DepthAttachment;
    }

    void OpenGLFramebuffer::Bind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
    }

    void OpenGLFramebuffer::Unbind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    static bool IsTextureAttachmentFormat(Texture2DInternalFormat format)
    {
        switch (format)
        {
            case Texture2DInternalFormat::R8:
            case Texture2DInternalFormat::RG8:
            case Texture2DInternalFormat::RGB8:
            case Texture2DInternalFormat::RGBA8:
            {
                return true;
            }
            default:
            {
                return false;
            }
        }
    }

    static bool IsDepthBufferAttachmentFormat(Texture2DInternalFormat format)
    {
        switch (format)
        {
            case Texture2DInternalFormat::Depth24Stencil8:
            {
                return true;
            }
            default:
            {
                return false;
            }
        }
    }

    Ref<Texture2D> OpenGLFramebuffer::CreateTextureAttachment(const FramebufferAttachmentSpecification &attachment)
    {
        if (IsTextureAttachmentFormat(attachment.TextureSpecification.InternalFormat))
        {
            return Texture2D::Create(attachment.TextureSpecification);
        }
        else
        {
            LOG_WARN("Framebuffer attachment format is not a texture format. Using RGBA8.");
            Texture2DSpecification spec {
                .Width = attachment.TextureSpecification.Width,
                .Height = attachment.TextureSpecification.Height,
                .InternalFormat = Texture2DInternalFormat::RGBA8,
                .DataFormat = Texture2DDataFormat::RGBA,
                .Filter = attachment.TextureSpecification.Filter,
                .Wrapping = attachment.TextureSpecification.Wrapping,
            };
            return Texture2D::Create(spec);
        }
    }

    Ref<Texture2D> OpenGLFramebuffer::CreateDepthBufferAttachment(const FramebufferAttachmentSpecification &attachment)
    {
        if (IsDepthBufferAttachmentFormat(attachment.TextureSpecification.InternalFormat))
        {
            return Texture2D::Create(attachment.TextureSpecification);
        }
        else
        {
            LOG_WARN("Framebuffer attachment format is not a depth buffer format. Using Depth24Stencil8.");
            Texture2DSpecification spec {
                .Width = attachment.TextureSpecification.Width,
                .Height = attachment.TextureSpecification.Height,
                .InternalFormat = Texture2DInternalFormat::Depth24Stencil8,
                .DataFormat = Texture2DDataFormat::DepthStencil,
                .Filter = attachment.TextureSpecification.Filter,
                .Wrapping = attachment.TextureSpecification.Wrapping,
            };
            return Texture2D::Create(spec);
        }
    }

    void OpenGLFramebuffer::ClearAttachments()
    {
        for (uint32_t i = 0; i < m_ColorAttachments.size(); i++)
        {
            ClearAttachment(i);
        }

        m_DepthAttachment.Texture->Clear(m_DepthAttachment.ClearValue);
    }

    void OpenGLFramebuffer::ClearAttachment(uint32_t index)
    {
        FramebufferAttachment &attachment = m_ColorAttachments[index];
        attachment.Texture->Clear(attachment.ClearValue);
    }

    void OpenGLFramebuffer::ResizeAttachment(uint32_t width, uint32_t height, uint32_t index)
    {
        glCreateFramebuffers(1, &m_RendererID);
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
        FramebufferAttachment &attachment = m_ColorAttachments[index];
        attachment.Texture->Resize(width, height);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, GL_TEXTURE_2D, attachment.Texture->GetRendererID(), 0);
    }

    void OpenGLFramebuffer::ResizeAttachments(uint32_t width, uint32_t height)
    {
        glCreateFramebuffers(1, &m_RendererID);
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
        for (uint32_t i = 0; i < m_ColorAttachments.size(); i++)
        {
            FramebufferAttachment &attachment = m_ColorAttachments[i];
            attachment.Texture->Resize(width, height);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, attachment.Texture->GetRendererID(), 0);
        }

        m_DepthAttachment.Texture->Resize(width, height);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment.Texture->GetRendererID(), 0);
    }

    void OpenGLFramebuffer::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
        glViewport(x, y, width, height);
    }


}