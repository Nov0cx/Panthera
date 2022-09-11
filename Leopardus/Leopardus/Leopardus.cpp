#include "Panthera/Panthera.hpp"

#include "Panthera/Core/Entry.hpp"

void ApplicationCreationCallback(Panthera::ApplicationInfo *outInfo)
{
    outInfo->Name = "Leopardus";
}

int PantheraMain(Panthera::Application *app)
{
    return 0;
}