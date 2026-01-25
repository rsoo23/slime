#include <Scene.hpp>
#include <RenderSystem.hpp>
#include <MovementSystem.hpp>
#include <UniformGrid.hpp>
#include <PheromoneDepositSystem.hpp>
#include <PheromoneDiffusionSystem.hpp>

Scene::Scene(const Config& config)
    : targetFPS(config.targetFPS),
    screenWidth(config.screenWidth),
    screenHeight(config.screenHeight),
    particleSpeed(config.particleSpeed),
    turnSpeed(config.turnSpeed),
    sensorDistance(config.sensorDistance),
    particleColor(config.particleColor),
    pheromoneLifetime(config.pheromoneLifetime),
    evaporationSpeed(config.evaporationSpeed),
    diffusionSpeed(config.diffusionSpeed),
    pheromoneColor(config.pheromoneColor),
    initType(config.initType),
    gridSize(config.gridSize),
    particleGap(config.particleGap),
    spawnProbability(config.spawnProbability),
    particleNum(config.particleNum),
    spawnRadius(config.spawnRadius),
    pheromoneGrid(config.screenWidth, config.screenHeight, config.gridSize)
{
    InitWindow(screenWidth, screenHeight, "ECS Slimulation");
    SetTargetFPS(targetFPS);
    initializeSlimeParticles();
}

void Scene::initializeSlimeParticles() {
    switch (initType) {
        case InitType::Random:
            initializeSlimeParticlesRandom();
            break;
        case InitType::CircleOutwards:
            initializeSlimeParticlesCircleOutwards();
            break;
        default:
            initializeSlimeParticlesCircleOutwards();
            break;
    }
}

void Scene::initializeSlimeParticlesRandom() {
    for (int h = 0; h < screenHeight; h += particleGap) {
        for (int w = 0; w < screenWidth; w += particleGap) {
            int hasSlimeParticle = GetRandomValue(0, (int)(1.0f / spawnProbability));

            if (hasSlimeParticle == 0) {
                Vector2 direction = {
                    (float)GetRandomValue(-100, 100) / 100.0f,
                    (float)GetRandomValue(-100, 100) / 100.0f
                };
                Vector2 normalizedDir = Vector2Normalize(direction);
                auto slimeParticle = registry.create();

                registry.emplace<SlimeParticle>(slimeParticle);
                registry.emplace<Position2D>(slimeParticle, Vector2{(float)w, (float)h});
                registry.emplace<Direction2D>(slimeParticle, Vector2(normalizedDir));
                registry.emplace<SlimeParticleRender>(slimeParticle, WHITE);
            }
        }
    }
}

void Scene::initializeSlimeParticlesCircleOutwards() {
    // Calculate center of screen
    Vector2 center = {screenWidth / 2.0f, screenHeight / 2.0f};
    
    for (int i = 0; i < particleNum; i++) {
        // Calculate angle for even distribution around circle
        float angle = (2.0f * PI * i) / particleNum;
        
        // Add some random variation to angle for more natural look
        float angleVariation = GetRandomValue(-30, 30) * DEG2RAD;
        angle += angleVariation;
        
        // Calculate spawn position on circle
        Vector2 spawnOffset = {
            cosf(angle) * spawnRadius,
            sinf(angle) * spawnRadius
        };
        Vector2 spawnPos = Vector2Add(center, spawnOffset);
        
        // Direction points radially outward from center (with some randomness)
        Vector2 radialDirection = Vector2Normalize(spawnOffset);
        // float dirVariation = GetRandomValue(-45, 45) * DEG2RAD;
        // Vector2 direction = Vector2Rotate(radialDirection, dirVariation);
        Vector2 direction = radialDirection;
        
        auto slimeParticle = registry.create();
        
        registry.emplace<SlimeParticle>(slimeParticle);
        registry.emplace<Position2D>(slimeParticle, spawnPos);
        registry.emplace<Direction2D>(slimeParticle, direction);
        registry.emplace<SlimeParticleRender>(slimeParticle, WHITE);
    }
}

Scene::~Scene() {
    CloseWindow();
}

void Scene::startScene() {
    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();

        PheromoneDepositSystem(registry, pheromoneLifetime, pheromoneGrid);
        MovementSystem(registry, deltaTime, screenHeight, screenWidth, pheromoneGrid, particleSpeed, turnSpeed, sensorDistance);
        PheromoneDiffusionSystem(registry, deltaTime, pheromoneGrid, diffusionSpeed, evaporationSpeed);

        BeginDrawing();
            ClearBackground(BLACK);
            
            RenderSystem(registry, pheromoneGrid);
        EndDrawing();
    }
}