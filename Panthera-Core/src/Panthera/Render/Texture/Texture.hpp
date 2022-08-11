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

    class Texture2D : public Texture
    {
    public:
        static Ref<Texture2D> Create(uint32_t width, uint32_t height);
        static Ref<Texture2D> Create(const std::string& path);
        virtual bool operator==(const Texture2D& other) const = 0;
    };
}

#endif //PANTHERA_TEXTURE_HPP
