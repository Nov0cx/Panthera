#ifndef PANTHERA_OPENGLFRAMEBUFFER_HPP
#define PANTHERA_OPENGLFRAMEBUFFER_HPP

#include "Panthera/Render/Framebuffer/Framebuffer.hpp"
#include "Panthera/Render/RenderAPI.hpp"

namespace Panthera
{
    class OpenGLFramebuffer : public Framebuffer
    {
    public:
        OpenGLFramebuffer(const std::initializer_list<FramebufferAttachmentSpecification>& attachments);
        ~OpenGLFramebuffer();

        virtual void AddAttachment(const FramebufferAttachmentSpecification& attachment) override;
        virtual void AddAttachments(const std::initializer_list<FramebufferAttachmentSpecification>& attachments) override;

        virtual FramebufferAttachment &GetAttachment(uint32_t index) override;
        virtual std::vector<FramebufferAttachment> &GetAttachments() override;
        virtual Ref<std::vector<FramebufferAttachment>> GetAttachments(FramebufferAttachmentType type) override;
        virtual Ref<std::vector<FramebufferAttachment>> GetAttachments(const std::initializer_list<FramebufferAttachmentType>& types) override;

        virtual void Bind() const override;
        virtual void Unbind() const override;
    private:
        std::vector<FramebufferAttachment> m_Attachments;
        Ref<Texture2D> CreateTextureAttachment(const FramebufferAttachmentSpecification& attachment);
        Ref<Texture2D> CreateDepthBufferAttachment(const FramebufferAttachmentSpecification& attachment);
        RendererID m_RendererID;
    };
}

#endif //PANTHERA_OPENGLFRAMEBUFFER_HPP
