#ifndef PANTHERA_OPENGLTEXTURE2D_HPP
#define PANTHERA_OPENGLTEXTURE2D_HPP

#include "ppch.hpp"
#include "Panthera/Renderer/Texture/Texture2D.hpp"

namespace Panthera
{
    class OpenGLTexture2D : public Texture2D
    {
    public:
        using RendererID = uint32_t;
    public:
        OpenGLTexture2D(const String& path);
        OpenGLTexture2D(const Texture2DInfo& info);
        ~OpenGLTexture2D();

        virtual void* GetRenderObject() const override;
        virtual Texture2DInfo& GetInfo() override;
        virtual const Texture2DInfo& GetInfo() const override;
        virtual void SetData(void* data, size_t size) override;

        virtual void Recreate(const String& path = "") override;

        virtual void Clear(int value = 0) override;
        virtual void Resize(uint32_t width, uint32_t height) override;

        virtual void SetWrapping(Texture2DWrapping wrapping) override;
        virtual void SetFiltering(Texture2DFiltering filtering) override;

        virtual bool operator==(const Texture2D& other) const override;

    private:
        void* LoadTexture(const String& path);
        void RecreateTexture();
    private:
        RendererID m_RendererID;
        Texture2DInfo m_Info;
        String m_Path;
    };
}

#endif //PANTHERA_OPENGLTEXTURE2D_HPP
