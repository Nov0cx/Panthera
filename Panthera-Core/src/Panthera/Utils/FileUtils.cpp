#include "FileUtils.hpp"

namespace Panthera::FileUtils
{

    String ReadFile(const String &filepath)
    {
        std::ifstream file(filepath);
        std::stringstream stream;
        stream << file.rdbuf();
        return stream.str();
    }

    String ReadFile(const std::filesystem::path &filepath)
    {
        std::ifstream file(filepath);
        std::stringstream stream;
        stream << file.rdbuf();
        return stream.str();
    }
}