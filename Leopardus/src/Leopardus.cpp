#include "Panthera/Panthera.hpp"

#include "LeopardusLayer.hpp"

namespace Panthera
{
    class LeopardusApp : public Application
    {
    public:
        LeopardusApp(const AppProps &props) : Application(props)
        {
            LeoparudsLayer *layer = new LeoparudsLayer();
            GetLayerStack()->PushLayout(layer);
        }
    };
}

int main(int argc, char **argv)
{
    Panthera::ProgramArgs args(argc, argv);
    Panthera::AppProps props(args, "Leopardus", 1920, 1080, false);
    Panthera::LeopardusApp app(props);

    app.Run();
    return 0;
}