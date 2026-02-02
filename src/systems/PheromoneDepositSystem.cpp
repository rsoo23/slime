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

        int gridIdx = pheromoneGrid.toIndex(pos.value.x, pos.value.y);

        pheromoneGrid.cells[gridIdx] = pheromoneLifetime;
    };
}