#include <entt.hpp>
#include <Components.hpp>
#include "includes/raymath.h"
#include <UniformGrid.hpp>

void RenderSystem(const entt::registry& registry, const UniformGrid& pheromoneGrid, const Color pheromoneColor) {
    const auto slimeView = registry.view<SlimeParticle, SlimeParticleRender, Position2D>();

    for (size_t i = 0; i < pheromoneGrid.cells.size(); ++i) {
        if (!pheromoneGrid.cells[i]) continue;
    
        const Color color = ColorLerp(BLACK, pheromoneColor, pheromoneGrid.cells[i]);

        const auto [x, y] = pheromoneGrid.toWorldCoord(i);

        DrawPixel(x, y, color);
    };

    for (const auto e : slimeView) {
        const auto& pos = slimeView.get<Position2D>(e);
        const auto& render = slimeView.get<SlimeParticleRender>(e);

        DrawPixel(pos.value.x, pos.value.y, render.color);
    };
}