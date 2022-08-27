#include "ImGuiLayer.hpp"

#include "Panthera/Render/Renderer.hpp"
#include "Panthera/Core/Log.hpp"
#include "Panthera/Core/Application.hpp"

#include "Platform/OpenGL/GUI/OpenGLImGui.hpp"
#include <cstring>

namespace Panthera
{

    void ImGuiLayer::OnStart()
    {
        switch (RendererState::GetAPI())
        {
            case RendererAPI::None:
                FAIL("RendererAPI::None is not supported!");
                break;
            case RendererAPI::OpenGL:
                m_ImGuiHelper = new OpenGLImGui();
                break;
            case RendererAPI::Vulkan:
                FAIL("RendererAPI::Vulkan is not supported!");
                break;
            case RendererAPI::Direct3D:
                FAIL("RendererAPI::Direct3D is not supported!");
                break;
            case RendererAPI::Metal:
                FAIL("RendererAPI::Metal is not supported!");
                break;
            default:
                FAIL("Unknown RendererAPI!");
                break;
        }

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();

        const char* path = (Application::GetInstance()->GetAssetPath("Panthera/Assets/GUI/imgui.ini")).c_str();
        char* heapPath = new char[strlen(path) + 1];
        strcpy(heapPath, path);
        io.IniFilename =  heapPath;

        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
        //io.ConfigViewportsNoAutoMerge = true;
        //io.ConfigViewportsNoTaskBarIcon = true;

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle &style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        m_ImGuiHelper->OnStart();
    }

    void ImGuiLayer::OnEnd()
    {
        m_ImGuiHelper->OnEnd();
        ImGuiIO &io = ImGui::GetIO();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::OnUpdate(Timestep ts)
    {}

    void ImGuiLayer::OnEvent(Event &event)
    {
        ImGuiIO &io = ImGui::GetIO();
        //event.SetCancelled(event.GetEventType() == EventType::MOUSE && io.WantCaptureMouse);
        //event.SetCancelled(event.GetEventType() == EventType::KEY && io.WantCaptureKeyboard);
    }

    void ImGuiLayer::Begin()
    {
        m_ImGuiHelper->Begin();
        ImGui::NewFrame();
        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_NoWindowMenuButton | ImGuiDockNodeFlags_NoCloseButton;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoCollapse;
        if (opt_fullscreen)
        {
            const ImGuiViewport *viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
                            ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        } else
        {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

        bool open = true;
        ImGui::Begin("Editor DockSpace", &open, window_flags);
        if (!opt_padding)
            ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // Submit the DockSpace
        ImGuiIO &io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("DockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }
    }

    void ImGuiLayer::End()
    {
        ImGui::End();
        ImGui::Render();
        m_ImGuiHelper->End();
    }

    void ImGuiLayer::SetIniPath(const std::string &path)
    {
        ImGui::GetIO().IniFilename = (path + "/imgui.ini").c_str();
    }
}