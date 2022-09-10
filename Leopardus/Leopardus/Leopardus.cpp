#include "Panthera/Core/Entry.hpp"
#include "ppch.hpp"

void ApplicationCreationCallback(Panthera::ApplicationInfo *outInfo)
{
    outInfo->Name = "Leopardus";
}

int PantheraMain(Panthera::Application *app)
{
    return 0;
}