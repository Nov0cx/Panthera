#ifndef PANTHERA_APPLICATION_HPP
#define PANTHERA_APPLICATION_HPP

#include "Layer.hpp"
#include "Panthera/Window/Window.hpp"
#include "Log.hpp"
#include "Pointer.hpp"
#include <string>
#include "Timestep.hpp"
#include "Panthera/Utils/Time.hpp"

#include "tools/cpp/runfiles/runfiles.h"
using bazel::tools::cpp::runfiles::Runfiles;

namespace Panthera
{
    struct ProgramArgs
    {
        int argc;
        char **argv;

        const char* operator[](int idx) const
        {
            ASSERT(idx < argc, "Index out of bounds!");
            return argv[idx];
        }

        char* operator[](int idx)
        {
            ASSERT(idx < argc, "Index out of bounds!");
            return argv[idx];
        }

        ProgramArgs(int argc, char **argv) : argc(argc), argv(argv)
        {}

        ProgramArgs() = default;
    };

    struct AppProps
    {
        AppProps(ProgramArgs args, const char *name, unsigned int width = 800, unsigned int height = 600, bool vSync = false);

        const char *Name;
        unsigned int Width;
        unsigned int Height;
        bool VSync;
        ProgramArgs Args;
    };

    class Application
    {
    public:
        static Application *GetInstance();

        Application(const AppProps &props);

        ~Application();

        void Run();

        void CallEvent(Event &event);

        // yeah a little mess because of Bazel
        std::string GetAssetPath(const char* filepath);

        LayerStack *GetLayerStack();

        uint32_t GetWindowWidth();
        uint32_t GetWindowHeight();

    private:
        static void SetInstance(void *instance);

        static Application *s_Instance;
    private:
        void Init(const AppProps &props);

    private:
        ProgramArgs m_Args;
        LayerStack m_LayerStack;
        bool m_Running = true;
        Ref<Window> m_Window;
        Runfiles* m_Runfiles;
        Timestep m_Timestep;
        Time::Time<std::chrono::seconds> m_LastFrameTime;
    };
}

#endif //PANTHERA_APPLICATION_HPP
