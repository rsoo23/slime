#pragma once
#include "includes/raylib.h"
#include "InitType.hpp"

struct Config {
    // Screen settings
    int targetFPS = 60;
    int screenWidth = 720;
    int screenHeight = 720;

    // Particle settings
    int particleSpeed = 100;
    float turnSpeed = 1000.f;
    float sensorDistance = 2.0f;
    Color particleColor = WHITE;

    // Pheromone settings
    int pheromoneLifetime = 1;
    float evaporationSpeed = 1.f;
    float diffusionSpeed = 10.f;
    Color pheromoneColor = BLUE;

    // Particle spawning settings
    InitType initType = InitType::CircleOutwards;

    // InitType::Random settings
    int gridSize = 1;
    int particleGap = 10;
    float spawnProbability = 0.5f;

    // InitType::CircleOutwards settings
    int particleNum = 50000;
    float spawnRadius = 200.f;
};