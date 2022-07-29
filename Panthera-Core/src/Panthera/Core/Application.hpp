#ifndef PANTHERA_APPLICATION_HPP
#define PANTHERA_APPLICATION_HPP

#include "Layer.hpp"

namespace Panthera
{
    class Application
    {
    public:
        static Application *GetInstance();

        Application();

        ~Application();

        void Run();

        void CallEvent(Event &event);

    private:
        static void SetInstance(void *instance);
        static Application *s_Instance;
    private:
        void Init();
    private:
        LayerStack m_LayerStack;
        bool m_Running = true;
    };
}

#endif //PANTHERA_APPLICATION_HPP
