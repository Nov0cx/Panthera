#include "Panthera/Panthera.hpp"

class Leopardus : public Panthera::Application {
public:
    Leopardus() : Panthera::Application() {

    }
};

int main(int argc, char** argv)
{
    TestInit();
    Leopardus app;

    app.Run();
    return 0;
}