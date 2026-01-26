#include <entt.hpp>
#include "includes/raylib.h"
#include "includes/raymath.h"
#include <Components.hpp>
#include <UniformGrid.hpp>
#include <iostream>

UniformGrid::UniformGrid(int width, int height, int cellSize)
    : width(width), height(height), cellSize(cellSize), 
      cells(width * height, 0.0f) {}

UniformGrid::~UniformGrid() {}

int UniformGrid::toIndex(int x, int y) {
    return y * width + x;
}

std::pair<int, int> UniformGrid::toWorldCoord(size_t index) {
    return {static_cast<int>(index % width), static_cast<int>(index / width)};
}

bool UniformGrid::checkPosWithinGrid(float worldX, float worldY) {
    int cx, cy;

    cx = static_cast<int>(worldX / cellSize);
    cy = static_cast<int>(worldY / cellSize);

    return cx >= 0 && cx < width && cy >= 0 && cy < height;
}
