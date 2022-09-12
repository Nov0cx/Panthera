#include "Panthera/Panthera.hpp"

#include "Panthera/Core/Entry.hpp"

void ApplicationCreationCallback(Panthera::ApplicationInfo *outInfo)
{
    outInfo->Name = "Leopardus";
    //PT_ASSERT(0 == 1, "Lol");
    Panthera::String test = "Hello";
    std::string test2 = "Hello";
    PT_LOG_INFO("Hello world!");
    PT_LOG_INFO("my string size {}, std string size {}", sizeof(Panthera::String), sizeof(std::string));
}

int PantheraMain(Panthera::Application *app)
{
    return 0;
}