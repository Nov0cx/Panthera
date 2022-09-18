#ifndef PANTHERA_FILEUTILS_HPP
#define PANTHERA_FILEUTILS_HPP

#include "ppch.hpp"

namespace Panthera::FileUtils
{
    String ReadFile(const String& filepath);
    String ReadFile(const std::filesystem::path& filepath);
}

#endif //PANTHERA_FILEUTILS_HPP
