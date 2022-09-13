#ifndef PANTHERA_ENTRY_HPP
#define PANTHERA_ENTRY_HPP

#include "ppch.hpp"
#include "Application.hpp"
#include "AssetLoader.hpp"

namespace Panthera
{
    extern void ApplicationCreationCallback(ApplicationInfo *outInfo);
    extern int Main(Application *app);

}


int pmain(int argc, char **argv)
{
    Panthera::AssetLoader::Init(argv[0]);

    Panthera::ApplicationInfo info;
    info.Args = Panthera::CommandLineArgs(argc, argv);
    Panthera::ApplicationCreationCallback(&info);

    Panthera::Application *app = Panthera::Application::Create(info);

    Panthera::Main(app);

    return 0;
}

int main(int argc, char **argv)
{
    return pmain(argc, argv);
}

#endif //PANTHERA_ENTRY_HPP
