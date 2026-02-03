#include <Scene.hpp>
#include <RenderSystem.hpp>
#include <MovementSystem.hpp>
#include <UniformGrid.hpp>
#include <PheromoneDepositSystem.hpp>
#include <PheromoneDiffusionSystem.hpp>

Scene::Scene(const Config& config)
    : config(config), pheromoneGrid(config.screenWidth, config.screenHeight)
{
    InitWindow(config.screenWidth, config.screenHeight, "ECS Slimulation");
    SetTargetFPS(config.targetFPS);
    initializeSlimeParticles();
}

void Scene::initializeSlimeParticles() {
    switch (config.initType) {
        case InitType::Random:
            initializeSlimeParticlesRandom();
            break;
        case InitType::CircleOutwards:
            initializeSlimeParticlesCircleOutwards();
            break;
        case InitType::CircleInwards:
            initializeSlimeParticlesCircleInwards();
            break;
        default:
            initializeSlimeParticlesCircleOutwards();
            break;
    }
}

void Scene::initializeSlimeParticlesRandom() {
    for (int h = 0; h < config.screenHeight; h += config.particleGap) {
        for (int w = 0; w < config.screenWidth; w += config.particleGap) {
            const int hasSlimeParticle = GetRandomValue(0, (int)(1.0f / config.spawnProbability));

            if (hasSlimeParticle == 0) {
                const Vector2 direction = {
                    (float)GetRandomValue(-100, 100) / 100.0f,
                    (float)GetRandomValue(-100, 100) / 100.0f
                };
                const Vector2 normalizedDir = Vector2Normalize(direction);
                const auto slimeParticle = registry.create();

                registry.emplace<SlimeParticle>(slimeParticle);
                registry.emplace<Position2D>(slimeParticle, Vector2{(float)w, (float)h});
                registry.emplace<Direction2D>(slimeParticle, Vector2(normalizedDir));
                registry.emplace<SlimeParticleRender>(slimeParticle, WHITE);
            }
        }
    }
}

void Scene::initializeSlimeParticlesCircleOutwards() {
    const Vector2 center = {config.screenWidth / 2.0f, config.screenHeight / 2.0f};
    
    for (int i = 0; i < config.particleNum; i++) {
        // Calculate angle for even distribution around circle
        const float angle = (2.0f * PI * i) / config.particleNum;
        
        // Calculate spawn position on circle
        const Vector2 spawnOffset = {
            cosf(angle) * config.spawnRadius,
            sinf(angle) * config.spawnRadius
        };
        const Vector2 spawnPos = Vector2Add(center, spawnOffset);
        
        // Direction points radially outward from center
        const Vector2 radialDirection = Vector2Normalize(spawnOffset);
        
        const auto slimeParticle = registry.create();
        
        registry.emplace<SlimeParticle>(slimeParticle);
        registry.emplace<Position2D>(slimeParticle, spawnPos);
        registry.emplace<Direction2D>(slimeParticle, radialDirection);
        registry.emplace<SlimeParticleRender>(slimeParticle, WHITE);
    }
}

void Scene::initializeSlimeParticlesCircleInwards() {
    const Vector2 center = {config.screenWidth / 2.0f, config.screenHeight / 2.0f};
    
    for (int i = 0; i < config.particleNum; i++) {
        // Calculate angle for even distribution around circle
        const float angle = (2.0f * PI * i) / config.particleNum;
        
        // Calculate spawn position on circle
        const Vector2 spawnOffset = {
            cosf(angle) * config.spawnRadius,
            sinf(angle) * config.spawnRadius
        };
        const Vector2 spawnPos = Vector2Add(center, spawnOffset);
        
        // Direction points radially inwards from center
        const Vector2 normalizedRadialDirection = Vector2Normalize(spawnOffset);
        const Vector2 radialDirection = Vector2Scale(normalizedRadialDirection, -1);
        
        const auto slimeParticle = registry.create();
        
        registry.emplace<SlimeParticle>(slimeParticle);
        registry.emplace<Position2D>(slimeParticle, spawnPos);
        registry.emplace<Direction2D>(slimeParticle, radialDirection);
        registry.emplace<SlimeParticleRender>(slimeParticle, WHITE);
    }
}

void Scene::initializeSlimeParticlesWithMouse() {
    const auto mousePosition = GetMousePosition();
    const auto slimeParticle = registry.create();

    const Vector2 direction = {
        (float)GetRandomValue(-100, 100) / 100.0f,
        (float)GetRandomValue(-100, 100) / 100.0f
    };
    const Vector2 normalizedDir = Vector2Normalize(direction);
    
    registry.emplace<SlimeParticle>(slimeParticle);
    registry.emplace<Position2D>(slimeParticle, mousePosition);
    registry.emplace<Direction2D>(slimeParticle, normalizedDir);
    registry.emplace<SlimeParticleRender>(slimeParticle, WHITE);
}

Scene::~Scene() {
    CloseWindow();
}

void Scene::startScene() {
    bool isPaused = false;

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_SPACE)) {
            isPaused = !isPaused;
        }

        const float deltaTime = GetFrameTime();

        if (!isPaused) {
            if (config.mouseDragSpawn && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                initializeSlimeParticlesWithMouse();
            }

            PheromoneDepositSystem(registry, config.pheromoneLifetime, pheromoneGrid);
            MovementSystem(registry, deltaTime, config.screenHeight, config.screenWidth, pheromoneGrid, config.particleSpeed, config.turnSpeed, config.sensorDistance);
            PheromoneDiffusionSystem(deltaTime, pheromoneGrid, config.diffusionSpeed, config.evaporationSpeed);
        }

        BeginDrawing();
            ClearBackground(BLACK);
            RenderSystem(registry, pheromoneGrid, config.pheromoneColor);
            if (isPaused) {
                DrawText("PAUSED", 10, 10, 30, RED);
            }
        EndDrawing();
    }
}