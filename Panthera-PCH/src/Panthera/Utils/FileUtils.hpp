#ifndef PANTHERA_FILEUTILS_HPP
#define PANTHERA_FILEUTILS_HPP

#include "ppch.hpp"

namespace Panthera::FileUtils
{
    const char* ReadFile(const String& filepath);
    const char* ReadFile(const std::filesystem::path& filepath);
}

#endif //PANTHERA_FILEUTILS_HPP
