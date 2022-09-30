#ifndef PANTHERA_TEXTURE2D_HPP
#define PANTHERA_TEXTURE2D_HPP

#include "ppch.hpp"

namespace Panthera
{
    enum class Texture2DWrapping
    {
        Repeat,
        MirroredRepeat,
        ClampToEdge,
        ClampToBorder
    };

    enum class Texture2DFiltering
    {
        Linear,
        Nearest
    };

    enum class Texture2DFormat
    {
        RGBA,
        RGB,
        RG,
        Red,
        Depth,
        Stencil,
        DepthStencil
    };

    struct Texture2DInfo
    {
        uint32_t Width = 0, Height = 0;
        uint32_t Channels = 1;
        Texture2DFormat Format = Texture2DFormat::Red;
        Texture2DWrapping Wrapping = Texture2DWrapping::ClampToEdge;
        Texture2DFiltering Filtering = Texture2DFiltering::Linear;
    };

    class Texture2D
    {
    public:
        static Ref<Texture2D> Create(const Texture2DInfo &info);
        static Ref<Texture2D> LoadFromDisk(const String &path);

    public:
        virtual void* GetRenderObject() const = 0;
        virtual Texture2DInfo& GetInfo() = 0;
        virtual const Texture2DInfo& GetInfo() const = 0;
        virtual void SetData(void* data, size_t size) = 0;

        virtual void Recreate(const String& path = "") = 0;

        virtual void Clear(int value = 0) = 0;
        virtual void Resize(uint32_t width, uint32_t height) = 0;

        virtual void SetWrapping(Texture2DWrapping wrapping) = 0;
        virtual void SetFiltering(Texture2DFiltering filtering) = 0;

        virtual bool operator==(const Texture2D& other) const = 0;

        virtual void Bind(uint32_t slot = 0) const = 0;
    };
}

#endif //PANTHERA_TEXTURE2D_HPP
