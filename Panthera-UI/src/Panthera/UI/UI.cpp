#include "UI.hpp"

#include "UIInternal.hpp"
#include "Panthera/Renderer/Renderer.hpp"

namespace Panthera::UI
{
    std::stack<String> ContextStack = {};
    std::vector<String> UnusedWindows = {};

    void Init()
    {
        Internal::Data::Init();
    }

    void BeginIteration()
    {
        UnusedWindows.clear();
        for (auto& window : Internal::Data::Instance->Windows)
            UnusedWindows.push_back(window.first);

        Internal::Data::Instance->Locked = false;
    }

    void EndIteration()
    {
        Internal::Data::Instance->Locked = true;

        if (UnusedWindows.empty())
            return;

        for (auto& window : UnusedWindows)
        {
            Internal::Data::Instance->Windows.erase(window);
        }
    }

    bool BeginContext(const String &name)
    {
        if (Internal::Data::Instance->Locked)
        {
            PT_LOG_ERROR("[UI] Cannot create a new window context while iteration is locked!");
            return false;
        }

        Ref<Window> window = nullptr;

        bool creation = false;

        if (Internal::Data::Instance->Windows.find(name) == Internal::Data::Instance->Windows.end())
        {
            creation = true;
            WindowInfo info;
            info.Title = name;
            info.Width = 1280;
            info.Height = 720;
            info.VSync = true;
            info.Fullscreen = false;

            window = GlobalRenderer::CreateAndGetWindow(info);
            window->Init();
            Internal::Data::Instance->AddWindow(name, window);
        }

        if (!window)
            window = Internal::Data::Instance->GetWindow(name);

        window->GetRenderContext()->MakeCurrent();

        ContextStack.push(name);

        if (!creation)
            UnusedWindows.erase(std::remove(UnusedWindows.begin(), UnusedWindows.end(), name), UnusedWindows.end());

        return true;
    }

    void EndContext()
    {
        if (Internal::Data::Instance->Locked)
        {
            PT_LOG_ERROR("[UI] Cannot end a window context while iteration is locked!");
            return;
        }

        if (ContextStack.empty())
        {
            PT_LOG_ERROR("[UI] EndContext() called without BeginContext()!");
            return;
        }

        String name = ContextStack.top();
        ContextStack.pop();

        Ref<Window> window = Internal::Data::Instance->GetWindow(name);

        PT_ASSERT(window, "[UI] Cannot get window with name: '{}'", name)

        window->GetRenderContext()->SwapBuffers();

        if (ContextStack.empty())
        {
            GlobalRenderer::GetMainWindow()->GetRenderContext()->MakeCurrent();
        }
        else
        {
            Internal::Data::Instance->Windows[ContextStack.top()]->GetRenderContext()->MakeCurrent();
        }
    }
}