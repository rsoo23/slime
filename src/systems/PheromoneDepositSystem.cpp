#include <entt.hpp>
#include <Components.hpp>
#include <UniformGrid.hpp>
#include <iostream>

void PheromoneDepositSystem(entt::registry& registry, int pheromoneLifetime, UniformGrid& pheromoneGrid) {
    auto view = registry.view<SlimeParticle, Position2D>();

    for (auto e : view) {
        auto& pos = view.get<Position2D>(e);

        if (!pheromoneGrid.checkPosWithinGrid(pos.value.x, pos.value.y)) {
            continue;
        }
        
        // convert world coordinates to grid coordinates
        int gridX = static_cast<int>(pos.value.x / pheromoneGrid.cellSize);
        int gridY = static_cast<int>(pos.value.y / pheromoneGrid.cellSize);
        
        int gridIdx = pheromoneGrid.toIndex(gridX, gridY);

        pheromoneGrid.cells[gridIdx] = pheromoneLifetime;
    };
}