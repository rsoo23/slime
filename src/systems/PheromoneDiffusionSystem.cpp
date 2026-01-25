#include <entt.hpp>
#include <Components.hpp>
#include <raymath.h>
#include <UniformGrid.hpp>
#include <iostream>

void PheromoneDiffusionSystem(entt::registry& registry, float deltaTime, UniformGrid& pheromoneGrid) {
    constexpr float evaporationSpeed = 1.f;
    constexpr float diffusionSpeed = 10.f;
    std::vector<float> tempCells = pheromoneGrid.cells;

    for (size_t i = 0; i < pheromoneGrid.cells.size(); ++i) {
        float totalPheromoneStrength = 0.f;

        auto [currX, currY] = pheromoneGrid.toWorldCoord(i);
        Vector2 currPos = {(float)currX, (float)currY};

        for (int offsetX = -1; offsetX <= 1; offsetX++) {
            for (int offsetY = -1; offsetY <= 1; offsetY++) {
                const Vector2 resultantPos = Vector2Add(currPos, Vector2{(float)offsetX, (float)offsetY});
                if (pheromoneGrid.checkPosWithinGrid(resultantPos.x, resultantPos.y)) {
                    int idx = pheromoneGrid.toIndex(resultantPos.x, resultantPos.y);
                    totalPheromoneStrength += pheromoneGrid.cells[idx];
                }
            }
        }

        float avgPheromoneStrength = totalPheromoneStrength / 9;

        float diffusedValue = Lerp(pheromoneGrid.cells[i], avgPheromoneStrength, diffusionSpeed * deltaTime);

        // Evaporation
        float diffusedAndEvaporatedValue = diffusedValue - evaporationSpeed * deltaTime;

        tempCells[i] = diffusedAndEvaporatedValue < 0.f ? 0.f : diffusedAndEvaporatedValue;
    };
    
    // Replace original grid with processed values
    pheromoneGrid.cells = std::move(tempCells);
}