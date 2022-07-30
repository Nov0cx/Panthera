#ifndef PANTHERA_OPENGLWINDOW_HPP
#define PANTHERA_OPENGLWINDOW_HPP

#include "Panthera/Window/Window.hpp"
#include "Panthera/Render/Renderer.hpp"

// fwd
typedef struct GLFWwindow GLFWwindow;

namespace Panthera
{
    class OpenGLWindow : public Window
    {
    public:
        OpenGLWindow(const WindowProps& props);
        ~OpenGLWindow();

        virtual void OnUpdate() override;
        virtual void OnEvent(Event& event) override;
        virtual std::any GetNativeWindow() const override;

        virtual uint32_t GetWidth() const override;
        virtual uint32_t GetHeight() const override;

        virtual void SetVSync(bool state) override;
        virtual bool IsVSync() const override;

        virtual bool ShouldBeClosed() const override;

    private:
        void Init(const char* title, uint32_t width, uint32_t height);

        GLFWwindow* m_Window;
        bool m_VSync;
        uint32_t m_Width, m_Height;
    };
}

#endif //PANTHERA_OPENGLWINDOW_HPP
