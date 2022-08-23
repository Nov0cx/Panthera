#include "OpenGLImGui.hpp"
#include "Panthera/Core/Application.hpp"
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <any>
#include <GLFW/glfw3.h>

namespace Panthera
{

    OpenGLImGui::OpenGLImGui()
    {}

    OpenGLImGui::~OpenGLImGui()
    {}

    void OpenGLImGui::Begin()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
    }

    void OpenGLImGui::End()
    {
        ImGuiIO &io = ImGui::GetIO();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow *backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }

    void OpenGLImGui::OnStart()
    {
        Ref<Window> window = Application::GetInstance()->GetWindow();

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(std::any_cast<GLFWwindow*>(window->GetNativeWindow()), true);
        ImGui_ImplOpenGL3_Init("#version 450");
    }

    void OpenGLImGui::OnEnd()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
    }
}