#include "FileUtils.hpp"

namespace Panthera::Utils
{

    std::string GetFileExtension(const std::string &path)
    {
        return std::filesystem::path(path).extension().string();
    }

    std::string GetFileExtension(const std::filesystem::path &path)
    {
        return path.extension().string();
    }

    std::string GetFileName(const std::filesystem::path &path)
    {
        return path.filename().string();
    }

    std::string GetFileName(const std::string &path)
    {
        return std::filesystem::path(path).filename().string();
    }
}