#pragma once
#include <entt.hpp>
#include <UniformGrid.hpp>

void PheromoneDiffusionSystem(entt::registry& registry, float deltaTime, UniformGrid& pheromoneGrid, float diffusionSpeed, float evaporationSpeed);