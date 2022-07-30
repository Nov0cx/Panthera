#include "Panthera/Panthera.hpp"

class Leopardus : public Panthera::Application {
public:
    Leopardus(const Panthera::AppProps& props) : Panthera::Application(props) {

    }
};

int main(int argc, char** argv)
{
    Panthera::AppProps props("Leopardus", 800, 600, false);
    Leopardus app(props);
    app.Run();
    return 0;
}