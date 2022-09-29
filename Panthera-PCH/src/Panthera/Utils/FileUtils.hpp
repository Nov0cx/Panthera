#ifndef PANTHERA_FILEUTILS_HPP
#define PANTHERA_FILEUTILS_HPP

#include "ppch.hpp"

namespace Panthera::FileUtils
{
    PT_API const char* ReadFile(const String& filepath);
    PT_API const char* ReadFile(const std::filesystem::path& filepath);
}

#endif //PANTHERA_FILEUTILS_HPP
