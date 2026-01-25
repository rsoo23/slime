#include "Config.hpp"
#include <Scene.hpp>

int main(int ac, char** argv) 
{
    Config config;

    if (ac >= 2) config.particleGap = std::atoi(argv[1]);
    if (ac >= 3) config.spawnProbability = std::atof(argv[2]);
    if (ac >= 4) config.pheromoneLifetime = std::atoi(argv[3]);
    if (ac >= 5) config.particleSpeed = std::atoi(argv[4]);

    Scene scene(config);
    scene.startScene();
}