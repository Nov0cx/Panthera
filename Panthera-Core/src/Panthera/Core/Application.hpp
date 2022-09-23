#ifndef PANTHERA_APPLICATION_HPP
#define PANTHERA_APPLICATION_HPP

#include "ppch.hpp"

#include "LayerSystem.hpp"
#include "Timestep.hpp"
#include "Version.hpp"

#include "Panthera/Renderer/Renderer.hpp"

extern int pmain(int argc, char **argv);

namespace Panthera
{
    struct CommandLineArgs
    {
        int argc;
        char **argv;

        CommandLineArgs(int argc, char **argv)
        {
            this->argc = argc;
            this->argv = argv;
        }

        CommandLineArgs()
        {
            this->argc = 0;
            this->argv = nullptr;
        }

        char* operator[](int index)
        {
            if (index >= argc)
                return nullptr;
            return argv[index];
        }
    };

    struct ApplicationInfo
    {
        String Name = "Panthera Application";
        Version Version = {0, 3, 0};
        CommandLineArgs Args = {};
        uint32_t Width = 0, Height = 0;
    };

    class Application
    {
    public:
        static inline Application *GetInstance()
        { return s_Instance; }

    public:
        ~Application();

        void Run();

        inline ApplicationInfo& GetInfo() { return m_Info; }
        inline const ApplicationInfo& GetInfo() const { return m_Info; }

        inline Ref<Window> GetMainWindow() { return GlobalRenderer::GetMainWindow(); }
        inline const Ref<Window> GetMainWindow() const { return GlobalRenderer::GetMainWindow(); }

        inline LayerStack* GetLayerStack() { return m_LayerStack; }
        inline const LayerStack* GetLayerStack() const { return m_LayerStack; }

        inline void PushLayer(Layer* layer) { m_LayerStack->PushLayer(layer); }
        inline void PopLayer(Layer* layer) { m_LayerStack->PopLayer(layer); }

        inline void PushOverlay(Layer* overlay) { m_LayerStack->PushOverlay(overlay); }
        inline void PopOverlay(Layer* overlay) { m_LayerStack->PopOverlay(overlay); }
    private:
        Application(ApplicationInfo &info);

    private:
        static Application *s_Instance;
        static Application *Create(ApplicationInfo &info);

    private:
        ApplicationInfo m_Info;
        LayerStack* m_LayerStack;
        float m_LastFrameTime = 0.0f;

        friend int ::pmain(int argc, char **argv);
    };
}

#endif //PANTHERA_APPLICATION_HPP
