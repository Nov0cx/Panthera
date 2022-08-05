#include "Panthera/Panthera.hpp"
#include <fstream>

class Leopardus : public Panthera::Application
{
public:
    Leopardus(const Panthera::AppProps &props) : Panthera::Application(props)
    {

    }
};

int main(int argc, char **argv)
{
    Panthera::ProgramArgs args(argc, argv);
    Panthera::AppProps props(args, "Leopardus", 800, 600, false);
    Leopardus app(props);
    auto path = app.GetAssetPath("Panthera/Assets/Shader/FlatColor.glsl");
    LOG_INFO("{}", path);
    auto shader = Panthera::ShaderLibrary::CreateShader("FlatColor", path);


    app.Run();
    return 0;
}