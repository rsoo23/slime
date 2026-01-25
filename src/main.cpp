#include <Scene.hpp>

int main(int ac, char** argv) 
{
    constexpr int screenWidth = 720;
    constexpr int screenHeight = 720;
    constexpr int targetFPS = 60;

    // default values
    int particleGap = 10;
    float spawnProbability = 0.5f;
    int pheromoneLifetime = 1;
    int particleSpeed = 100;

    if (ac >= 2) particleGap = std::atoi(argv[1]);
    if (ac >= 3) spawnProbability = std::atof(argv[2]);
    if (ac >= 4) pheromoneLifetime = std::atoi(argv[3]);
    if (ac >= 5) particleSpeed = std::atoi(argv[4]);

    Scene scene(targetFPS, screenWidth, screenHeight, particleGap, spawnProbability, pheromoneLifetime, particleSpeed);

    scene.startScene();
}