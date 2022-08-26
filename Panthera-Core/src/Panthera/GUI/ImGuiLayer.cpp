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
    }

    void ImGuiLayer::End()
    {
        ImGui::Render();
        m_ImGuiHelper->End();
    }

    void ImGuiLayer::SetIniPath(const std::string &path)
    {
        ImGui::GetIO().IniFilename = (path + "/imgui.ini").c_str();
    }
}