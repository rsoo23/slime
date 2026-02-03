#pragma once
#include <entt.hpp>
#include "includes/raylib.h"
#include "includes/raymath.h"
#include <Components.hpp>

class UniformGrid {
    public:
        UniformGrid(int width, int height);
        ~UniformGrid();

        int width;
        int height;

        std::vector<float> cells;

        int toIndex(int x, int y) const;
        std::pair<int, int> toWorldCoord(size_t index) const;
        bool checkPosWithinGrid(float worldX, float worldY) const;
};