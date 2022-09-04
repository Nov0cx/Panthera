#include "ContentBrowserPanel.hpp"

namespace Panthera
{

    static const std::string AssetDirectory = "Assets";

    void Clamp1(float &value)
    {
        if (value < 1.f) value = 1.f;
    }

    ContentBrowserPanel::ContentBrowserPanel()
    {
        m_CurrentPath = AssetDirectory;
        auto app = Application::GetInstance();
        m_FileIcon = Texture2D::Create(
                Texture2DSpecification{.Path = app->GetAssetPath(
                        "Panthera/Assets/GUI/File.png").c_str(), .Wrapping = Texture2DWrapping::ClampToEdge});
        m_DirectoryIcon = Texture2D::Create(
                Texture2DSpecification{.Path = app->GetAssetPath(
                        "Panthera/Assets/GUI/Directory.png").c_str(), .Wrapping = Texture2DWrapping::ClampToEdge});
    }

    void ContentBrowserPanel::Render()
    {
        ImGui::Begin("Content Browser");

        if (m_CurrentPath != std::filesystem::path(AssetDirectory))
        {
            if (ImGui::Button(".."))
            {
                m_CurrentPath = m_CurrentPath.parent_path();
            }
        }

        static float cellWidth = 160.0f;
        static float cellHeight = 160.0f;
        static float cellPadding = 12.0f;

        float panelWidth = ImGui::GetContentRegionAvail().x;

        float cellCountX = panelWidth / (cellWidth + cellPadding);
        Clamp1(cellCountX);

        ImGui::Columns(cellCountX, 0, false);

        for (auto &entry: std::filesystem::directory_iterator(m_CurrentPath))
        {
            ImGui::PushID(entry.path().string().c_str());

            Ref <Texture2D> &icon = entry.is_directory() ? m_DirectoryIcon : m_FileIcon;

            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));

            ImGui::ImageButton((void *) icon->GetRendererID(), ImVec2(cellWidth, cellHeight), ImVec2(0, 1),
                               ImVec2(1, 0), 0);


            if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceNoDisableHover))
            {
                std::string path = entry.path().string();
                ImGui::SetDragDropPayload("CONTENT_BROWSER_ITEM", path.c_str(),
                                          path.size() + 1);
                ImGui::EndDragDropSource();
            }

            ImGui::PopStyleColor();

            if (ImGui::IsItemClicked())
            {
                if (entry.is_directory())
                {
                    m_CurrentPath /= entry.path().filename();
                }
            }

            ImGui::TextWrapped(entry.path().filename().string().c_str());

            ImGui::NextColumn();

            ImGui::PopID();
        }

        ImGui::Columns(1);

        ImGui::End();
    }
}