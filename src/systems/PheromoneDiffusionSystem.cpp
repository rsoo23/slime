#include <entt.hpp>
#include <Components.hpp>
#include "includes/raymath.h"
#include <UniformGrid.hpp>
#include <iostream>

void PheromoneDiffusionSystem(const float deltaTime, UniformGrid& pheromoneGrid, const float diffusionSpeed, const float evaporationSpeed) {
    std::vector<float> tempCells = pheromoneGrid.cells;

    for (size_t i = 0; i < pheromoneGrid.cells.size(); ++i) {
        float totalPheromoneStrength = 0.f;

        const auto [currX, currY] = pheromoneGrid.toWorldCoord(i);
        const Vector2 currPos = {(float)currX, (float)currY};

        for (int offsetX = -1; offsetX <= 1; offsetX++) {
            for (int offsetY = -1; offsetY <= 1; offsetY++) {
                const Vector2 resultantPos = Vector2Add(currPos, Vector2{(float)offsetX, (float)offsetY});
                if (pheromoneGrid.checkPosWithinGrid(resultantPos.x, resultantPos.y)) {
                    const int idx = pheromoneGrid.toIndex(resultantPos.x, resultantPos.y);
                    totalPheromoneStrength += pheromoneGrid.cells[idx];
                }
            }
        }

        const float avgPheromoneStrength = totalPheromoneStrength / 9;

        const float diffusedValue = Lerp(pheromoneGrid.cells[i], avgPheromoneStrength, diffusionSpeed * deltaTime);

        // Evaporation
        const float diffusedAndEvaporatedValue = diffusedValue - evaporationSpeed * deltaTime;

        tempCells[i] = diffusedAndEvaporatedValue < 0.f ? 0.f : diffusedAndEvaporatedValue;
    };
    
    // Replace original grid with processed values
    pheromoneGrid.cells = std::move(tempCells);
}