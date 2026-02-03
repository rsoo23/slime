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
        const Config& config;

        UniformGrid pheromoneGrid;
        
        void initializeSlimeParticles();
        void initializeSlimeParticlesRandom();
        void initializeSlimeParticlesCircleOutwards();
        void initializeSlimeParticlesCircleInwards();
        void initializeSlimeParticlesWithMouse();
};