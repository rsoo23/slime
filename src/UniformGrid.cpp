#include <entt.hpp>
#include "includes/raylib.h"
#include "includes/raymath.h"
#include <Components.hpp>
#include <UniformGrid.hpp>
#include <iostream>

UniformGrid::UniformGrid(int width, int height)
    : width(width), height(height), cells(width * height, 0.0f) {}

UniformGrid::~UniformGrid() {}

int UniformGrid::toIndex(int x, int y) {
    return y * width + x;
}

std::pair<int, int> UniformGrid::toWorldCoord(size_t index) {
    return {static_cast<int>(index % width), static_cast<int>(index / width)};
}

bool UniformGrid::checkPosWithinGrid(float worldX, float worldY) {
    return worldX >= 0 && worldX < width && worldY >= 0 && worldY < height;
}
