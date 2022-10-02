#ifndef PANTHERA_FRAMEBUFFER_HPP
#define PANTHERA_FRAMEBUFFER_HPP

#include "ppch.hpp"
#include "Panthera/Renderer/Texture/Texture2D.hpp"

namespace Panthera
{
    struct ColorAttachmentInfo
    {
        Texture2DFormat Format = Texture2DFormat::RGBA;
        uint32_t Samples = 1;
        //bool SwapChainTarget = false;
    };

    struct DepthAttachmentInfo
    {
        Texture2DFormat Format = Texture2DFormat::None;
        uint32_t Samples = 1;
        //bool SwapChainTarget = false;
    };

    struct FramebufferInfo
    {
        uint32_t Width = 0, Height = 0;
        std::vector<ColorAttachmentInfo> ColorAttachments = { };
        DepthAttachmentInfo DepthAttachment;

        bool SwapChainTarget = false;

        FramebufferInfo() = default;
        FramebufferInfo(uint32_t width, uint32_t height)
            : Width(width), Height(height) {}
        FramebufferInfo(uint32_t width, uint32_t height, std::initializer_list<ColorAttachmentInfo> colorAttachments, DepthAttachmentInfo depthAttachment = {})
            : Width(width), Height(height), ColorAttachments(colorAttachments), DepthAttachment(depthAttachment) {}
    };

    class Framebuffer
    {
    public:
        static Ref<Framebuffer> Create(const FramebufferInfo &info);
    public:
        virtual ~Framebuffer() = default;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual void Resize(uint32_t width, uint32_t height) = 0;

        virtual void* GetColorAttachmentRenderObject(uint32_t index = 0) const = 0;
        virtual std::vector<Ref<Texture2D>> &GetColorAttachments() = 0;
        virtual Ref<Texture2D> &GetColorAttachment(uint32_t index = 0) = 0;
        virtual const Ref<Texture2D> &GetDepthAttachment() const = 0;

        virtual const FramebufferInfo &GetInfo() const = 0;

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;
    };
}

#endif //PANTHERA_FRAMEBUFFER_HPP
