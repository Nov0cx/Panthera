#ifndef PANTHERA_TEXTURE_HPP
#define PANTHERA_TEXTURE_HPP

#include "Panthera/Core/Pointer.hpp"
#include <cinttypes>
#include <string>

namespace Panthera
{
    // fwd
    using RendererID = uint32_t;

    class Texture
    {
    public:
        virtual void Bind(uint32_t slot = 0) = 0;
        virtual void Unbind() = 0;
        virtual void SetData(void* data, uint32_t size) = 0;

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;

        virtual RendererID GetRendererID() const = 0;
        virtual bool IsLoaded() const = 0;
    };

    enum class Texture2DInternalFormat
    {
        R8,
        RG8,
        RGB8,
        RGBA8,
    };

    enum class Texture2DDataFormat
    {
        Red,
        RG,
        RGB,
        RGBA,
    };

    enum class Texture2DFilter
    {
        Nearest,
        Linear,
    };

    enum class Texture2DWrapping
    {
        ClampToEdge,
        Repeat,
    };

    struct Texture2DSpecification
    {
        uint32_t Width = 1, Height = 1;
        const char* Path = "";
        Texture2DInternalFormat InternalFormat = Texture2DInternalFormat::RGBA8;
        Texture2DDataFormat DataFormat = Texture2DDataFormat::RGBA;
        Texture2DFilter Filter = Texture2DFilter::Linear;
        Texture2DWrapping Wrapping = Texture2DWrapping::Repeat;
    };

    class Texture2D : public Texture
    {
    public:
        static Ref<Texture2D> Create(const Texture2DSpecification& spec);
        virtual bool operator==(const Texture2D& other) const = 0;
    };
}

#endif //PANTHERA_TEXTURE_HPP
