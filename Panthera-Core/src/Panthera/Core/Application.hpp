#ifndef PANTHERA_APPLICATION_HPP
#define PANTHERA_APPLICATION_HPP

#include "Layer.hpp"
#include "Panthera/Window/Window.hpp"

namespace Panthera
{
    struct AppProps
    {
        AppProps(const char *name, unsigned int width = 800, unsigned int height = 600, bool vSync = false);

        const char* Name;
        unsigned int Width;
        unsigned int Height;
        bool VSync;
    };

    class Application
    {
    public:
        static Application *GetInstance();

        Application(const AppProps &props);

        ~Application();

        void Run();

        void CallEvent(Event &event);

    private:
        static void SetInstance(void *instance);
        static Application *s_Instance;
    private:
        void Init(const AppProps &props);
    private:
        LayerStack m_LayerStack;
        bool m_Running = true;
        Ref<Window> m_Window;
    };
}

#endif //PANTHERA_APPLICATION_HPP
