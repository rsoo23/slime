#pragma once
#include <entt.hpp>
#include "../UniformGrid.hpp"

void MovementSystem(entt::registry& registry, const float deltaTime, const int screenHeight, const int screenWidth, const UniformGrid& pheromoneGrid, const int speed, const float turnSpeed, const float sensorDistance);
