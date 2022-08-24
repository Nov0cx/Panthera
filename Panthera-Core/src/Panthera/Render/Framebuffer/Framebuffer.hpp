#ifndef PANTHERA_FRAMEBUFFER_HPP
#define PANTHERA_FRAMEBUFFER_HPP

#include "Panthera/Render/Texture/Texture.hpp"
#include <initializer_list>
#include <vector>
#include "Panthera/Core/Pointer.hpp"

namespace Panthera
{
    enum class FramebufferAttachmentType
    {
        Color,
        Depth,
    };

    struct FramebufferAttachmentSpecification
    {
        FramebufferAttachmentType AttachmentType;
        Texture2DSpecification TextureSpecification;
        int ClearValue = 0;
    };

    struct FramebufferAttachment
    {
        FramebufferAttachmentType AttachmentType;
        Ref<Texture2D> Texture;
        int ClearValue = 0;
        uint32_t Width, Height;
    };

    class Framebuffer
    {
    public:
        static Ref<Framebuffer> Create(const std::initializer_list<FramebufferAttachmentSpecification>& attachments);

        virtual void AddAttachment(const FramebufferAttachmentSpecification& attachment) = 0;
        virtual void AddAttachments(const std::initializer_list<FramebufferAttachmentSpecification>& attachments) = 0;

        virtual FramebufferAttachment &GetColorAttachment(uint32_t index) = 0;
        virtual std::vector<FramebufferAttachment> &GetColorAttachments() = 0;
        virtual Ref<std::vector<FramebufferAttachment>> GetAttachments(FramebufferAttachmentType type) = 0;
        virtual Ref<std::vector<FramebufferAttachment>> GetAttachments(const std::initializer_list<FramebufferAttachmentType>& types) = 0;

        virtual FramebufferAttachment &GetDepthAttachment() = 0;

        virtual void ClearAttachments() = 0;
        virtual void ClearAttachment(uint32_t index) = 0;

        virtual void ResizeAttachment(uint32_t width, uint32_t height, uint32_t index) = 0;
        virtual void ResizeAttachments(uint32_t width, uint32_t height) = 0;
        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
    private:
    };
}

#endif //PANTHERA_FRAMEBUFFER_HPP
