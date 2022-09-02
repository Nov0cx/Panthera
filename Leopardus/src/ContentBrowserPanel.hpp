#ifndef PANTHERA_CONTENTBROWSERPANEL_HPP
#define PANTHERA_CONTENTBROWSERPANEL_HPP

#include "Panthera/Panthera.hpp"

#include <filesystem>

namespace Panthera
{
    class ContentBrowserPanel
    {
    public:
        ContentBrowserPanel();

        void Render();

    private:
        std::filesystem::path m_CurrentPath;
    };
}

#endif //PANTHERA_CONTENTBROWSERPANEL_HPP
