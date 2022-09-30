#include "Texture2D.hpp"

#ifdef PANTHERA_OPENGL
#include "Panthera/Platform/OpenGL/Texture/OpenGLTexture2D.hpp"
#endif

namespace Panthera
{

    Ref <Texture2D> Texture2D::Create(const Texture2DInfo &info)
    {
#ifdef PANTHERA_OPENGL
        return Ref<OpenGLTexture2D>::Create(info);
#endif
    }

    Ref <Texture2D> Texture2D::LoadFromDisk(const String &path)
    {
#ifdef PANTHERA_OPENGL
        return Ref<OpenGLTexture2D>::Create(path);
#endif
    }
}