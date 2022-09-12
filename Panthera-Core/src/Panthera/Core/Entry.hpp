#ifndef PANTHERA_ENTRY_HPP
#define PANTHERA_ENTRY_HPP

#include "ppch.hpp"
#include "Application.hpp"
#include "AssetLoader.hpp"

extern void ApplicationCreationCallback(Panthera::ApplicationInfo *outInfo);

extern int PantheraMain(Panthera::Application *app);

int pmain(int argc, char **argv)
{
    Panthera::AssetLoader::Init(argv[0]);

    Panthera::ApplicationInfo info;
    info.Args = Panthera::CommandLineArgs(argc, argv);
    ApplicationCreationCallback(&info);

    Panthera::Application *app = Panthera::Application::Create(info);

    PantheraMain(app);

    return 0;
}

int main(int argc, char **argv)
{
    return pmain(argc, argv);
}

#endif //PANTHERA_ENTRY_HPP
