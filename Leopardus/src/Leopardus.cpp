#include "Panthera/Panthera.hpp"

class Leopardus : public Panthera::Application {

};

int main(int argc, char** argv)
{
    TestInit();
    Leopardus app;
    Application::SetInstance(&app);
    app.Run();
    return 0;
}