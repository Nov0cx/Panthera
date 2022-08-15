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

    Ref<Texture2D> OpenGLFramebuffer::CreateTextureAttachment(const FramebufferAttachmentSpecification &attachment)
    {
        Texture2DSpecification spec {
            .Width = Application::GetInstance()->GetWindow()->GetWidth(),
            .Height = Application::GetInstance()->GetWindow()->GetHeight(),
        };
        Ref<Texture2D> tex = Texture2D::Create(spec);
        return tex;
    }

    Ref<Texture2D> OpenGLFramebuffer::CreateDepthBufferAttachment(const FramebufferAttachmentSpecification &attachment)
    {
        Texture2DSpecification spec {
                .Width = Application::GetInstance()->GetWindow()->GetWidth(),
                .Height = Application::GetInstance()->GetWindow()->GetHeight(),
        };
        Ref<Texture2D> tex = Texture2D::Create(spec);
        return tex;
    }

}