#ifndef PANTHERA_GLFWWINDOW_HPP
#define PANTHERA_GLFWWINDOW_HPP

#include "Panthera/Window/Window.hpp"
#include "Panthera/Render/Renderer.hpp"

#include "Panthera/Window/RenderContext.hpp"

// fwd
typedef struct GLFWwindow GLFWwindow;

namespace Panthera
{
    class GLFWWindow : public Window
    {
    public:
        GLFWWindow(const WindowProps &props);

        ~GLFWWindow();

        virtual void OnUpdate() override;

        virtual void OnEvent(Event &event) override;

        virtual std::any GetNativeWindow() const override;

        virtual uint32_t GetWidth() const override;

        virtual uint32_t GetHeight() const override;

        virtual void SetVSync(bool state) override;

        virtual bool IsVSync() const override;

        virtual bool ShouldBeClosed() const override;

    private:
        void Init(const char *title, uint32_t width, uint32_t height);

        struct WindowInfo
        {
            uint32_t Width, Height;
            std::string Name;
            bool VSync;
        } m_Info;

        GLFWwindow *m_Window;

        Ref <RenderContext> m_Context;
    };
}

#endif //PANTHERA_GLFWWINDOW_HPP
