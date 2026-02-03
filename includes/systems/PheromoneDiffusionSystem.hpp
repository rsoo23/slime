#pragma once
#include <entt.hpp>
#include <UniformGrid.hpp>

void PheromoneDiffusionSystem(const float deltaTime, UniformGrid& pheromoneGrid, const float diffusionSpeed, const float evaporationSpeed);