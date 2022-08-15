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
                case FramebufferAttachmentType::Red:
                case FramebufferAttachmentType::RG:
                case FramebufferAttachmentType::RGB:
                case FramebufferAttachmentType::RGBA:
                {
                    Ref<Texture2D> tex = CreateTextureAttachment(attachment);
                    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + m_Attachments.size(), GL_TEXTURE_2D, tex->GetRendererID(), 0);
                    m_Attachments.push_back({attachment.AttachmentType, tex});
                    break;
                }
                case FramebufferAttachmentType::Depth:
                case FramebufferAttachmentType::Stencil:
                case FramebufferAttachmentType::DepthStencil:
                {
                    Ref<Texture2D> tex = CreateDepthBufferAttachment(attachment);
                    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, tex->GetRendererID(), 0);
                    m_Attachments.push_back({attachment.AttachmentType, tex});
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

    }

    void
    OpenGLFramebuffer::AddAttachments(const std::initializer_list <FramebufferAttachmentSpecification> &attachments)
    {

    }

    FramebufferAttachment &OpenGLFramebuffer::GetAttachment(uint32_t index)
    {
        return m_Attachments[index];
    }

    std::vector <FramebufferAttachment> &OpenGLFramebuffer::GetAttachments()
    {
        return m_Attachments;
    }

    Ref <std::vector<FramebufferAttachment>> OpenGLFramebuffer::GetAttachments(FramebufferAttachmentType type)
    {
        Ref <std::vector<FramebufferAttachment>> attachments = CreateRef<std::vector<FramebufferAttachment>>();
        for (auto &attachment: m_Attachments)
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
        for (auto &attachment: m_Attachments)
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

}