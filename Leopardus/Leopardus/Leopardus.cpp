#include "Panthera/Panthera.hpp"

#include "Panthera/Core/Entry.hpp"

void ApplicationCreationCallback(Panthera::ApplicationInfo *outInfo)
{
    outInfo->Name = "Leopardus";
    //PT_ASSERT(0 == 1, "Lol");
    Panthera::String test = "Hello";
    std::string test2 = "Hello";
    PT_LOG_INFO("Hello world!");
    PT_LOG_TRACE("my string size {}, std string size {}", sizeof(Panthera::String), sizeof(std::string));
    PT_ASSERT_HANDLE(false, []() {
        PT_LOG_ERROR("ASSERT HANDLE FAILED");
    });
    PT_LOG_FATAL("FATAL");
    PT_LOG_WARNING("WARNING");
    std::cout << "Hello world!" << std::endl;
}

int PantheraMain(Panthera::Application *app)
{
    return 0;
}