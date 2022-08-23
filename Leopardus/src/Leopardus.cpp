#include "Panthera/Panthera.hpp"

#include "LeopardusLayer.hpp"

class LeopardusApp : public Panthera::Application
{
public:
    LeopardusApp(const Panthera::AppProps &props) : Panthera::Application(props)
    {
        auto layer = Panthera::CreateRef<Leopardus();
        GetLayerStack()->PushLayout(layer);
    }
};

int main(int argc, char **argv)
{
    Panthera::ProgramArgs args(argc, argv);
    Panthera::AppProps props(args, "Leopardus", 1920, 1080, false);
    Leopardus app(props);

    app.Run();
    return 0;
}