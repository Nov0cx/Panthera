#ifndef PANTHERA_FILEUTILS_HPP
#define PANTHERA_FILEUTILS_HPP

#include <filesystem>

namespace Panthera::Utils
{
    std::string GetFileExtension(const std::string& path);
    std::string GetFileExtension(const std::filesystem::path& path);
    std::string GetFileName(const std::filesystem::path& path);
    std::string GetFileName(const std::string& path);
}

#endif //PANTHERA_FILEUTILS_HPP
