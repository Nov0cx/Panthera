#ifndef PANTHERA_ASSETLOADER_HPP
#define PANTHERA_ASSETLOADER_HPP

#include "DLL.hpp"
#include "StringBase.hpp"

namespace Panthera::AssetLoader
{
    PT_API void Init(const String &arg0);
    PT_API String GetAssetPath(const String &path);
}

#endif //PANTHERA_ASSETLOADER_HPP
