#pragma once
#include <entt.hpp>
#include "raylib.h"
#include <UniformGrid.hpp>

void RenderSystem(const entt::registry& registry, const UniformGrid& pheromoneGrid, const Color pheromoneColor);