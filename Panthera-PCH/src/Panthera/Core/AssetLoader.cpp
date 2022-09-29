#include "AssetLoader.hpp"

#include "LOG.hpp"
#include "tools/cpp/runfiles/runfiles.h"
using bazel::tools::cpp::runfiles::Runfiles;

namespace Panthera::AssetLoader
{
    static Runfiles* s_Runfiles;

    PT_API String GetAssetPath(const String &path)
    {
        return s_Runfiles->Rlocation(path);
    }

    PT_API void Init(const String &arg0)
    {
        String error;
        s_Runfiles = Runfiles::Create(arg0, (std::string*)&error);
        PT_ASSERT(s_Runfiles, "Failed to create runfiles: {}", (char*)error);
    }
}