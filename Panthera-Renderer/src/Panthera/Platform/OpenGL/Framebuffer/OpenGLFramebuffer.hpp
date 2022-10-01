#ifndef PANTHERA_OPENGLFRAMEBUFFER_HPP
#define PANTHERA_OPENGLFRAMEBUFFER_HPP

#include "ppch.hpp"
#include "Panthera/Renderer/Framebuffer/Framebuffer.hpp"

namespace Panthera
{
    class OpenGLFramebuffer : public Framebuffer
    {
    public:
        using RendererID = uint32_t;
    public:
        OpenGLFramebuffer(const FramebufferInfo &info);
        virtual ~OpenGLFramebuffer();

        virtual void Bind() override;
        virtual void Unbind() override;

        virtual void Resize(uint32_t width, uint32_t height) override;

        virtual void* GetColorAttachmentRenderObject(uint32_t index = 0) const override;
        virtual const std::vector<Ref<Texture2D>> &GetColorAttachments() const override;
        virtual const Ref<Texture2D> &GetDepthAttachment() const override;

        virtual const FramebufferInfo &GetInfo() const override;

        virtual uint32_t GetWidth() const override;
        virtual uint32_t GetHeight() const override;

    private:
        RendererID m_RendererID;
        FramebufferInfo m_Info;
        std::vector<Ref<Texture2D>> m_ColorAttachments;
        Ref<Texture2D> m_DepthAttachment;
    };
}

#endif //PANTHERA_OPENGLFRAMEBUFFER_HPP
