#ifndef PANTHERA_OPENGLTEXTURE_HPP
#define PANTHERA_OPENGLTEXTURE_HPP

#include "Panthera/Render/Texture/Texture.hpp"
#include "Panthera/Render/RenderAPI.hpp"

namespace Panthera
{
    class OpenGLTexture2D : public Texture2D
    {
    public:
        OpenGLTexture2D(const Texture2DSpecification& spec);
        ~OpenGLTexture2D();

        void Bind(uint32_t slot = 0) override;
        void Unbind() override;
        void SetData(void* data, uint32_t size) override;

        uint32_t GetWidth() const override;
        uint32_t GetHeight() const override;

        RendererID GetRendererID() const override;
        bool IsLoaded() const override;

        bool operator==(const Texture2D& other) const override;

        virtual Texture2DFilter GetFilter() const override;
        virtual Texture2DInternalFormat GetInternalFormat() const override;
        virtual Texture2DDataFormat GetDataFormat() const override;
        virtual Texture2DWrapping GetWrapping() const override;

        const char* GetPath() const override;

        void Clear(int value = 0) override;
    private:
        RendererID m_RendererID;
        uint32_t m_Width, m_Height;
        bool m_IsLoaded;
        uint32_t m_CurrentSlot = 0;
        uint32_t m_Format, m_DataFormat;
        const char* m_Path;
        Texture2DFilter m_Filter;
        Texture2DInternalFormat m_InternalFormatEnum;
        Texture2DDataFormat m_DataFormatEnum;
        Texture2DWrapping m_Wrapping;
    };
}

#endif //PANTHERA_OPENGLTEXTURE_HPP
