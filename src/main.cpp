#include "Config.hpp"
#include <Scene.hpp>

int main(int ac, char** argv) 
{
    Config config;

    if (ac >= 2) config.pheromoneLifetime = std::atoi(argv[1]);
    if (ac >= 3) config.particleSpeed = std::atoi(argv[2]);

    Scene scene(config);
    scene.startScene();
}