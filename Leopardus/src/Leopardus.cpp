#include "Panthera/Panthera.hpp"

class Leopardus : public Panthera::Application {
public:
    Leopardus() : Panthera::Application() {

    }
};

int main(int argc, char** argv)
{
    Leopardus app;
    LOG_INFO("Hello, world!")
    TestInit();
    app.Run();
    return 0;
}