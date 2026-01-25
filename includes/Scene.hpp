#pragma once
#include <entt.hpp>
#include <raylib.h>
#include <raymath.h>
#include <Components.hpp>
#include "UniformGrid.hpp"

class Scene {
    public:
        Scene(int targetFPS, int width, int height, int gap, float probability, int pheromoneLifetime, int particleSpeed);
        ~Scene();

        void startScene();

        entt::registry registry;

    private:
        int targetFPS;
        int screenWidth;
        int screenHeight;
        int particleGap;
        float spawnProbability;
        int pheromoneLifetime;
        int particleSpeed;
        UniformGrid pheromoneGrid;
        
        void initializeSlimeParticles();
        void initializePheromoneGrid();
};