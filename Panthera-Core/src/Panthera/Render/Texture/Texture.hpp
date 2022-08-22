#ifndef PANTHERA_TEXTURE_HPP
#define PANTHERA_TEXTURE_HPP

#include "Panthera/Core/Pointer.hpp"
#include <cinttypes>
#include <string>

namespace Panthera
{
    // fwd
    using RendererID = uint32_t;

    enum class Texture2DInternalFormat
    {
        R8,
        RG8,
        RGB8,
        RGBA8,
        Depth24Stencil8,
    };

    static const char *Texture2DInternalFormatToString(Texture2DInternalFormat format)
    {
        switch (format)
        {
            case Texture2DInternalFormat::R8:
                return "R8";
            case Texture2DInternalFormat::RG8:
                return "RG8";
            case Texture2DInternalFormat::RGB8:
                return "RGB8";
            case Texture2DInternalFormat::RGBA8:
                return "RGBA8";
            case Texture2DInternalFormat::Depth24Stencil8:
                return "Depth24Stencil8";
            default:
                return "";
        }
    }

    static Texture2DInternalFormat StringToTexture2DInternalFormat(const std::string& format)
    {
        if (format == "R8")
            return Texture2DInternalFormat::R8;
        else if (format == "RG8")
            return Texture2DInternalFormat::RG8;
        else if (format == "RGB8")
            return Texture2DInternalFormat::RGB8;
        else if (format == "RGBA8")
            return Texture2DInternalFormat::RGBA8;
        else if (format == "Depth24Stencil8")
            return Texture2DInternalFormat::Depth24Stencil8;
        else
            return Texture2DInternalFormat::R8;
    }

    enum class Texture2DDataFormat
    {
        Red,
        RG,
        RGB,
        RGBA,
        DepthStencil,
    };

    static const char *Texture2DDataFormatToString(Texture2DDataFormat format)
    {
        switch (format)
        {
            case Texture2DDataFormat::Red:
                return "Red";
            case Texture2DDataFormat::RG:
                return "RG";
            case Texture2DDataFormat::RGB:
                return "RGB";
            case Texture2DDataFormat::RGBA:
                return "RGBA";
            case Texture2DDataFormat::DepthStencil:
                return "DepthStencil";
            default:
                return "";
        }
    }

    static Texture2DDataFormat StringToTexture2DDataFormat(const std::string &str)
    {
        if (str == "Red")
            return Texture2DDataFormat::Red;
        else if (str == "RG")
            return Texture2DDataFormat::RG;
        else if (str == "RGB")
            return Texture2DDataFormat::RGB;
        else if (str == "RGBA")
            return Texture2DDataFormat::RGBA;
        else if (str == "DepthStencil")
            return Texture2DDataFormat::DepthStencil;
        else
            return Texture2DDataFormat::Red;
    }

    enum class Texture2DFilter
    {
        Nearest,
        Linear,
    };

    static const char *Texture2DFilterToString(Texture2DFilter filter)
    {
        switch (filter)
        {
            case Texture2DFilter::Nearest:
                return "Nearest";
            case Texture2DFilter::Linear:
                return "Linear";
            default:
                return "";
        }
    }

    static Texture2DFilter StringToTexture2DFilter(const std::string &str)
    {
        if (str == "Nearest")
        {
            return Texture2DFilter::Nearest;
        }
        else if (str == "Linear")
        {
            return Texture2DFilter::Linear;
        }
        else
        {
            return Texture2DFilter::Nearest;
        }
    }

    enum class Texture2DWrapping
    {
        ClampToEdge,
        Repeat,
    };

    static const char *Texture2DWrappingToString(Texture2DWrapping wrapping)
    {
        switch (wrapping)
        {
            case Texture2DWrapping::ClampToEdge:
                return "ClampToEdge";
            case Texture2DWrapping::Repeat:
                return "Repeat";
            default:
                return "";
        }
    }

    static Texture2DWrapping Texture2DWrappingFromString(const std::string &str)
    {
        if (str == "ClampToEdge")
        {
            return Texture2DWrapping::ClampToEdge;
        }
        else if (str == "Repeat")
        {
            return Texture2DWrapping::Repeat;
        }
        else
        {
            return Texture2DWrapping::Repeat;
        }
    }

    class Texture
    {
    public:
        virtual void Bind(uint32_t slot = 0) = 0;

        virtual void Unbind() = 0;

        virtual void SetData(void *data, uint32_t size) = 0;

        virtual uint32_t GetWidth() const = 0;

        virtual uint32_t GetHeight() const = 0;

        virtual RendererID GetRendererID() const = 0;

        virtual bool IsLoaded() const = 0;

        virtual const char *GetPath() const = 0;
    };

    struct Texture2DSpecification
    {
        uint32_t Width = 1, Height = 1;
        const char *Path = "";
        Texture2DInternalFormat InternalFormat = Texture2DInternalFormat::RGBA8;
        Texture2DDataFormat DataFormat = Texture2DDataFormat::RGBA;
        Texture2DFilter Filter = Texture2DFilter::Linear;
        Texture2DWrapping Wrapping = Texture2DWrapping::Repeat;
    };

    class Texture2D : public Texture
    {
    public:
        static Ref <Texture2D> Create(const Texture2DSpecification &spec);

        virtual bool operator==(const Texture2D &other) const = 0;
        virtual Texture2DFilter GetFilter() const = 0;
        virtual Texture2DInternalFormat GetInternalFormat() const = 0;
        virtual Texture2DDataFormat GetDataFormat() const = 0;
        virtual Texture2DWrapping GetWrapping() const = 0;
    };
}

#endif //PANTHERA_TEXTURE_HPP
