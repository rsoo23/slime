#include <entt.hpp>
#include <Components.hpp>
#include "includes/raymath.h"
#include <UniformGrid.hpp>

void RenderSystem(entt::registry& registry, UniformGrid& pheromoneGrid, Color pheromoneColor) {
    auto slimeView = registry.view<SlimeParticle, SlimeParticleRender, Position2D>();

    for (size_t i = 0; i < pheromoneGrid.cells.size(); ++i) {
        if (!pheromoneGrid.cells[i]) continue;
    
        Color color = ColorLerp(BLACK, pheromoneColor, pheromoneGrid.cells[i]);

        auto [x, y] = pheromoneGrid.toWorldCoord(i);

        DrawPixel(x, y, color);
    };

    for (auto e : slimeView) {
        auto& pos = slimeView.get<Position2D>(e);
        auto& render = slimeView.get<SlimeParticleRender>(e);

        DrawPixel(pos.value.x, pos.value.y, render.color);
    };
}