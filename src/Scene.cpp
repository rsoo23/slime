
#include <Scene.hpp>
#include <RenderSystem.hpp>
#include <MovementSystem.hpp>
#include <PheromoneLifetimeSystem.hpp>
#include <UniformGrid.hpp>
#include <PheromoneDepositSystem.hpp>
#include <PheromoneDiffusionSystem.hpp>

Scene::Scene(int targetFPS, int width, int height, int gap, float probability, int pheromoneLifetime, int particleSpeed) 
    : targetFPS(targetFPS), screenWidth(width), screenHeight(height), particleGap(gap), 
    spawnProbability(probability), pheromoneLifetime(pheromoneLifetime), particleSpeed(particleSpeed),
    pheromoneGrid(width, height, 1) {
    
    InitWindow(screenWidth, screenHeight, "ECS Slimulation");
    SetTargetFPS(targetFPS);
    
    initializeSlimeParticles();
}

void Scene::initializeSlimeParticles() {
    // for (int h = 0; h < screenHeight; h += particleGap) {
    //     for (int w = 0; w < screenWidth; w += particleGap) {
    //         int hasSlimeParticle = GetRandomValue(0, (int)(1.0f / spawnProbability));

    //         if (hasSlimeParticle == 0) {
    //             Vector2 direction = {
    //                 (float)GetRandomValue(-100, 100) / 100.0f,
    //                 (float)GetRandomValue(-100, 100) / 100.0f
    //             };
    //             Vector2 normalizedDir = Vector2Normalize(direction);
    //             auto slimeParticle = registry.create();

    //             registry.emplace<SlimeParticle>(slimeParticle);
    //             registry.emplace<Position2D>(slimeParticle, Vector2{(float)w, (float)h});
    //             registry.emplace<Direction2D>(slimeParticle, Vector2(normalizedDir));
    //             registry.emplace<SlimeParticleRender>(slimeParticle, WHITE);
    //         }
    //     }
    // }

    // for (int h = 0; h < screenHeight; h += particleGap) {
    //     for (int w = 0; w < screenWidth; w += particleGap) {
    //         if (w == 360 || w == 361) {
    //             Vector2 direction = {
    //                 (float)GetRandomValue(-100, 100) / 100.0f,
    //                 (float)GetRandomValue(-100, 100) / 100.0f
    //             };
    //             Vector2 normalizedDir = Vector2Normalize(direction);
    //             auto slimeParticle = registry.create();

    //             registry.emplace<SlimeParticle>(slimeParticle);
    //             registry.emplace<Position2D>(slimeParticle, Vector2{(float)w, (float)h});
    //             registry.emplace<Direction2D>(slimeParticle, Vector2(normalizedDir));
    //             registry.emplace<SlimeParticleRender>(slimeParticle, WHITE);
    //         }
    //     }
    // }

    // Calculate center of screen
    Vector2 center = {screenWidth / 2.0f, screenHeight / 2.0f};
    
    // Number of particles to spawn
    int numParticles = static_cast<int>(5000); // Adjust based on spawn probability
    float spawnRadius = 5.0f; // Radius from center to spawn particles
    
    for (int i = 0; i < numParticles; i++) {
        // Calculate angle for even distribution around circle
        float angle = (2.0f * PI * i) / numParticles;
        
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

        // Call systems directly since UpdateSimulation is in main.cpp
        PheromoneDepositSystem(registry, pheromoneLifetime, pheromoneGrid);
        MovementSystem(registry, deltaTime, screenHeight, screenWidth, pheromoneGrid, particleSpeed);
        // PheromoneLifetimeSystem(registry, deltaTime, pheromoneGrid);
        PheromoneDiffusionSystem(registry, deltaTime, pheromoneGrid);

        BeginDrawing();
            ClearBackground(BLACK);
            
            RenderSystem(registry, pheromoneGrid);
        EndDrawing();
    }
}