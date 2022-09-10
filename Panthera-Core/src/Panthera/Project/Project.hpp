#ifndef PANTHERA_PROJECT_HPP
#define PANTHERA_PROJECT_HPP

#include <string>
#include <vector>
#include "Panthera/Scene/Scene.hpp"
#include "Panthera/Scene/SceneSerializer.hpp"
#include "Panthera/Render/RenderAPI.hpp"
#include "Panthera/Render/Renderer.hpp"
#include "Panthera/Utils/MiscUtils.hpp"
#include "Panthera/Core/Log.hpp"

namespace Panthera
{
    class Project
    {
    public:
        Project(const std::string &name, const std::string &path, RendererAPI api = RendererAPI::OpenGL);

        ~Project();

        inline void AddScene(Ref <Scene> scene)
        {
            if (Utils::STLVector::Contains(m_Scenes, scene, [](const Ref<Scene>& a, const Ref<Scene>& b) { return a->GetName() == b->GetName(); }))
                return;

            m_Scenes.push_back(scene);
            if (!m_ActiveScene)
            {
                SetActiveScene(scene);
            }
        }

        void RemoveScene(Ref <Scene> scene);

        inline const std::vector <Ref<Scene>> &GetScenes() const
        { return m_Scenes; }

        inline const std::string &GetName() const
        { return m_Name; }

        inline void SetName(const std::string &name)
        { m_Name = name; }

        inline const std::string &GetPath() const
        { return m_Path; }

        inline void SetPath(const std::string &path)
        { m_Path = path; }

        inline RendererAPI GetRendererAPI() const
        { return m_RendererAPI; }

        inline Ref <Scene> GetActiveScene()
        { return m_ActiveScene; }

        void SetActiveScene(const std::string &name);

        inline void SetActiveScene(Ref <Scene> scene)
        {
            m_ActiveScene = scene;
            m_ActiveScene->SetDropCallback([this](std::string &filePath)
                                           {
                                               auto scene1 = SceneSerializer::Deserialize(filePath);
                                               m_NextActiveScene = scene1;
                                               AddScene(scene1);
                                           });
        }

        inline void SetRendererAPI(RendererAPI api)
        {
            m_RendererAPI = api;
            RendererState::SetAPI(api);
        }

        inline void Update()
        {
            if (m_NextActiveScene)
            {
                SetActiveScene(m_NextActiveScene);
                m_NextActiveScene = nullptr;
            }
        }

    private:
        std::vector <Ref<Scene>> m_Scenes = {};
        Ref <Scene> m_ActiveScene = nullptr;
        Ref <Scene> m_NextActiveScene = nullptr;
        std::string m_Name;
        std::string m_Path;
        RendererAPI m_RendererAPI;
    };
}

#endif //PANTHERA_PROJECT_HPP
