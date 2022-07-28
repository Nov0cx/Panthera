#ifndef PANTHERA_APPLICATION_HPP
#define PANTHERA_APPLICATION_HPP

namespace Panthera {
    class Application {
    public:
        static Application* GetInstance();
        Application();
        ~Application();

        void Run();

    private:
        static void SetInstance(void *instance);
        static Application* s_Instance;
    };
}

#endif //PANTHERA_APPLICATION_HPP
