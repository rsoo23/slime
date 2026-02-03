#include <entt.hpp>
#include <Components.hpp>
#include <UniformGrid.hpp>
#include <iostream>

void PheromoneDepositSystem(const entt::registry& registry, const int pheromoneLifetime, UniformGrid& pheromoneGrid) {
    const auto view = registry.view<SlimeParticle, Position2D>();

    for (const auto e : view) {
        const auto& pos = view.get<Position2D>(e);

        if (!pheromoneGrid.checkPosWithinGrid(pos.value.x, pos.value.y)) {
            continue;
        }

        const int gridIdx = pheromoneGrid.toIndex(pos.value.x, pos.value.y);

        pheromoneGrid.cells[gridIdx] = pheromoneLifetime;
    };
}