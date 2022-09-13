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

        void SetVSync(bool enabled) override;
        bool IsVSync() const override;

        WindowInfo& GetInfo() override;
        const WindowInfo& GetInfo() const override;

    private:
        void Shutdown();
    private:
        void* m_Window = nullptr;
        WindowInfo m_Info;
        bool m_IsShutDown = false;
    };
}

#endif //PANTHERA_WINDOWSWINDOW_HPP
