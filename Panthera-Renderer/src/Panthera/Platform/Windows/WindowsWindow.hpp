#ifndef PANTHERA_WINDOWSWINDOW_HPP
#define PANTHERA_WINDOWSWINDOW_HPP

#include "Panthera/Renderer/Window/Window.hpp"

namespace Panthera
{
    class WindowsWindow : public Window
    {
    public:
        WindowsWindow(const WindowInfo &info);
        virtual ~WindowsWindow();

        void Init() override;
        void Update() override;

        void* GetNativeWindow() override;

        void SetFullScreen(bool state, void* monitor = nullptr) override;
        void SetMaximized(bool state) override;

        void SetVSync(bool enabled) override;
        bool IsVSync() const override;

        Ref<RenderContext> GetRenderContext() const override;

        WindowInfo& GetInfo() override;
        const WindowInfo& GetInfo() const override;

        virtual bool operator ==(const Window& other) const override;
        virtual bool operator !=(const Window& other) const override;
    private:
        void Shutdown();
    private:
        void* m_Window = nullptr;
        Ref<RenderContext> m_Context = nullptr;
        WindowInfo m_Info {};
        bool m_IsShutDown = false;
        int m_PosX = 0, m_PosY = 0;
    };
}

#endif //PANTHERA_WINDOWSWINDOW_HPP
