#pragma once
#include <entt.hpp>
#include "../UniformGrid.hpp"

void MovementSystem(entt::registry& registry, float deltaTime, int screenHeight, int screenWidth, UniformGrid& pheromoneGrid, int speed);
