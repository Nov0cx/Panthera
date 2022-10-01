#include "OpenGLFramebuffer.hpp"

#include <glad/glad.h>

namespace Panthera
{

    OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferInfo &info)
    {
        m_Info = info;

        glCreateFramebuffers(1, &m_RendererID);
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

        for (uint32_t i = 0; i < info.ColorAttachments.size(); i++)
        {
            Texture2DInfo texInfo;
            texInfo.Width = info.Width;
            texInfo.Height = info.Height;
            texInfo.Format = info.ColorAttachments[i].Format;
            Ref<Texture2D> texture = Texture2D::Create(texInfo);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, *(uint32_t*)texture->GetRenderObject(), 0);
            m_ColorAttachments.push_back(texture);
        }

        if (info.DepthAttachment.Format != Texture2DFormat::None)
        {
            Texture2DInfo texInfo;
            texInfo.Width = info.Width;
            texInfo.Height = info.Height;
            texInfo.Format = info.DepthAttachment.Format;
            m_DepthAttachment = Texture2D::Create(texInfo);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, *(uint32_t*)m_DepthAttachment->GetRenderObject(), 0);
        }

        PT_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    OpenGLFramebuffer::~OpenGLFramebuffer()
    {
        glDeleteFramebuffers(1, &m_RendererID);
    }

    void OpenGLFramebuffer::Bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
    }

    void OpenGLFramebuffer::Unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void OpenGLFramebuffer::Resize(uint32_t width, uint32_t height)
    {
        m_Info.Width = width;
        m_Info.Height = height;

        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

        for (uint32_t i = 0; i < m_ColorAttachments.size(); i++)
        {
            m_ColorAttachments[i]->Resize(width, height);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, *(uint32_t*)m_ColorAttachments[i]->GetRenderObject(), 0);
        }

        if (m_DepthAttachment)
        {
            m_DepthAttachment->Resize(width, height);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, *(uint32_t*)m_DepthAttachment->GetRenderObject(), 0);
        }

        PT_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void *OpenGLFramebuffer::GetColorAttachmentRenderObject(uint32_t index) const
    {
        return m_ColorAttachments[index]->GetRenderObject();
    }

    const std::vector <Ref<Texture2D>> &OpenGLFramebuffer::GetColorAttachments() const
    {
        return m_ColorAttachments;
    }

    const Ref <Texture2D> &OpenGLFramebuffer::GetDepthAttachment() const
    {
        return m_DepthAttachment;
    }

    const FramebufferInfo &OpenGLFramebuffer::GetInfo() const
    {
        return m_Info;
    }

    uint32_t OpenGLFramebuffer::GetWidth() const
    {
        return m_Info.Width;
    }

    uint32_t OpenGLFramebuffer::GetHeight() const
    {
        return m_Info.Height;
    }
}