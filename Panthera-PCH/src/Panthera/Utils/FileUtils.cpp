#include "FileUtils.hpp"

namespace Panthera::FileUtils
{

    const char* ReadFile(const String &filepath)
    {
        std::ifstream file(filepath.Get(), std::ios::in);
        std::stringstream stream;
        stream << file.rdbuf();
        file.close();
        return stream.str().c_str();
    }

    const char* ReadFile(const std::filesystem::path &filepath)
    {
        std::ifstream file(filepath, std::ios::in);
        std::stringstream stream;
        stream << file.rdbuf();
        file.close();
        return stream.str().c_str();
    }
}