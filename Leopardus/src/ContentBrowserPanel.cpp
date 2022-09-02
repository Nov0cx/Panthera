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
        static float cellPadding = 12.0f;

        float panelWidth = ImGui::GetContentRegionAvail().x;

        float cellCountX = panelWidth / (cellWidth + cellPadding);
        Clamp1(cellCountX);

        ImGui::Columns(cellCountX, 0, false);

        for (auto& entry : std::filesystem::directory_iterator(m_CurrentPath))
        {
            ImGui::PushID(entry.path().string().c_str());
            if (entry.is_directory())
            {
                if (ImGui::Button(entry.path().filename().string().c_str()))
                {
                    m_CurrentPath = entry.path();
                }
            }
            else
            {
                if (ImGui::Button(("File: " + entry.path().filename().string()).c_str()))
                {

                }
            }

            ImGui::NextColumn();

            ImGui::PopID();
        }

        ImGui::Columns(1);

        ImGui::End();
    }
}