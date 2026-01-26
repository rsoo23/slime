#pragma once
#include <entt.hpp>
#include "includes/raylib.h"
#include "includes/raymath.h"
#include <Components.hpp>
#include "UniformGrid.hpp"
#include "Config.hpp"

class Scene {
    public:
        Scene(const Config& config);
        ~Scene();

        void startScene();

        entt::registry registry;

    private:
        int targetFPS;
        int screenWidth;
        int screenHeight;

        int particleSpeed;
        float turnSpeed;
        float sensorDistance;
        Color particleColor;

        int pheromoneLifetime;
        float evaporationSpeed;
        float diffusionSpeed;
        Color pheromoneColor;

        InitType initType;

        float gridSize;
        int particleGap;
        float spawnProbability;

        int particleNum;
        float spawnRadius;


        UniformGrid pheromoneGrid;
        
        void initializeSlimeParticles();
        void initializeSlimeParticlesRandom();
        void initializeSlimeParticlesCircleOutwards();
        void initializeSlimeParticlesCircleInwards();
};