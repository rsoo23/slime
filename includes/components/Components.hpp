#pragma once
#include <includes/raylib.h>

struct SlimeParticle {};

struct Pheromone {};

struct Position2D {
    Vector2 value;
};

struct Direction2D {
    Vector2 value;
};

struct Lifetime {
    float remaining;
    float total;
};

struct PheromoneRender {
    Color color;
};

struct SlimeParticleRender {
    Color color;
};
