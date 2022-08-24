#ifndef PANTHERA_OPENGLFRAMEBUFFER_HPP
#define PANTHERA_OPENGLFRAMEBUFFER_HPP

#include "Panthera/Render/Framebuffer/Framebuffer.hpp"
#include "Panthera/Render/RenderAPI.hpp"

namespace Panthera
{
    // TODO only one depth attachment is supported
    class OpenGLFramebuffer : public Framebuffer
    {
    public:
        OpenGLFramebuffer(const std::initializer_list<FramebufferAttachmentSpecification>& attachments);
        ~OpenGLFramebuffer();

        virtual void AddAttachment(const FramebufferAttachmentSpecification& attachment) override;
        virtual void AddAttachments(const std::initializer_list<FramebufferAttachmentSpecification>& attachments) override;

        virtual FramebufferAttachment &GetColorAttachment(uint32_t index) override;
        virtual std::vector<FramebufferAttachment> &GetColorAttachments() override;
        virtual Ref<std::vector<FramebufferAttachment>> GetAttachments(FramebufferAttachmentType type) override;
        virtual Ref<std::vector<FramebufferAttachment>> GetAttachments(const std::initializer_list<FramebufferAttachmentType>& types) override;

        virtual FramebufferAttachment &GetDepthAttachment() override;

        virtual void ClearAttachments() override;
        virtual void ClearAttachment(uint32_t index) override;

        virtual void ResizeAttachment(uint32_t width, uint32_t height, uint32_t index) override;
        virtual void ResizeAttachments(uint32_t width, uint32_t height) override;
        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

        virtual void Bind() const override;
        virtual void Unbind() const override;
    private:
        std::vector<FramebufferAttachment> m_ColorAttachments;
        FramebufferAttachment m_DepthAttachment;
        Ref<Texture2D> CreateTextureAttachment(const FramebufferAttachmentSpecification& attachment);
        Ref<Texture2D> CreateDepthBufferAttachment(const FramebufferAttachmentSpecification& attachment);
        RendererID m_RendererID;
    };
}

#endif //PANTHERA_OPENGLFRAMEBUFFER_HPP
