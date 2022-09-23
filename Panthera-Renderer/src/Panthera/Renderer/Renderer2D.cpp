#include "Renderer2D.hpp"

#include <glad/glad.h>
#include "Renderer.hpp"

namespace Panthera
{

    struct Renderer2DStorage
    {

    };

    void Renderer2D::Init()
    {
        m_Storage = new Renderer2DStorage();
    }

    void Renderer2D::Shutdown()
    {
        delete m_Storage;
    }

    void Renderer2D::DrawIndexed()
    {

    }
}