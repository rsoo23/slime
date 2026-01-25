#include <entt.hpp>
#include <Components.hpp>
#include <raymath.h>
#include <raylib.h>
#include <UniformGrid.hpp>
#include <iostream>

float samplePheromoneValue(Vector2 particlePos, Vector2 sensorDir, UniformGrid& pheromoneGrid, float sensorDistance = 10.0f) {
    // calc sensor world pos by moving sensorDistance units in sensor direction
    Vector2 sensorOffset = Vector2Scale(Vector2Normalize(sensorDir), sensorDistance);
    Vector2 sensorWorldPos = Vector2Add(particlePos, sensorOffset);
    
    // check if sensor position is within grid bounds
    if (!pheromoneGrid.checkPosWithinGrid(sensorWorldPos.x, sensorWorldPos.y)) {
        return 0.0f; // return 0 if out of bounds
    }
    
    // convert world pos to grid coordinates
    int gridX = static_cast<int>(sensorWorldPos.x / pheromoneGrid.cellSize);
    int gridY = static_cast<int>(sensorWorldPos.y / pheromoneGrid.cellSize);
    
    // convert grid coordinates to array index
    int frontSensorGridIdx = pheromoneGrid.toIndex(gridX, gridY);
    
    // sample pheromone value
    return pheromoneGrid.cells[frontSensorGridIdx];
};

void MovementSystem(entt::registry& registry, float deltaTime, int screenHeight, int screenWidth, UniformGrid& pheromoneGrid, int particleSpeed) {
    auto view = registry.view<SlimeParticle, Position2D, Direction2D>();
    
    const float sensorDistance = 2.0f; // distance ahead to place sensors
    const float turnSpeed = 1000.f;

    for (auto e : view) {
        auto& particlePos = view.get<Position2D>(e);
        auto& frontSensorDir = view.get<Direction2D>(e);

        Vector2 newDir;
        
        // ensure direction is normalized
        frontSensorDir.value = Vector2Normalize(frontSensorDir.value);
        
        // sample front pheromone value
        float frontPheromoneVal = samplePheromoneValue(particlePos.value, frontSensorDir.value, pheromoneGrid, sensorDistance);
        // std::cout << "Front Pheromone Value: " << frontPheromoneVal << std::endl;

        // sample left pheromone value (45 degrees left)
        Vector2 leftSensorDir = Vector2Rotate(frontSensorDir.value, -45 * DEG2RAD);
        float leftPheromoneVal = samplePheromoneValue(particlePos.value, leftSensorDir, pheromoneGrid, sensorDistance);

        // std::cout << "Front Pheromone Value: " << frontPheromoneVal << std::endl;
        // sample right pheromone value (45 degrees right)
        Vector2 rightSensorDir = Vector2Rotate(frontSensorDir.value, 45 * DEG2RAD);
        float rightPheromoneVal = samplePheromoneValue(particlePos.value, rightSensorDir, pheromoneGrid, sensorDistance);

        float randomSteerStrength = GetRandomValue(0, 100) / 100.f;

        // compare pheromone values and decide direction
        if ((frontPheromoneVal > leftPheromoneVal) && (frontPheromoneVal > rightPheromoneVal)) {
            newDir = frontSensorDir.value;
        } else if ((frontPheromoneVal < leftPheromoneVal) && (frontPheromoneVal < rightPheromoneVal)) {
            float angle = (randomSteerStrength - 0.5f) * 2 * turnSpeed * deltaTime;
            newDir = Vector2Rotate(frontSensorDir.value, angle * DEG2RAD);
        } else if (leftPheromoneVal > rightPheromoneVal) {
            float angle = -randomSteerStrength * turnSpeed * deltaTime; // negative for left
            newDir = Vector2Rotate(frontSensorDir.value, angle * DEG2RAD);
        } else if (rightPheromoneVal > leftPheromoneVal) {
            float angle = randomSteerStrength * turnSpeed * deltaTime; // positive for right
            newDir = Vector2Rotate(frontSensorDir.value, angle * DEG2RAD);
        } else {
            newDir = frontSensorDir.value;
        }

        // update direction and calculate movement
        frontSensorDir.value = newDir;

        Vector2 velocity = Vector2Scale(frontSensorDir.value, particleSpeed * deltaTime);
        Vector2 newPos = Vector2Add(particlePos.value, velocity);

        // if newPos is out of bounds then move in opposite direction
        if (newPos.x < 0 || newPos.x > screenWidth) {
            frontSensorDir.value.x = -frontSensorDir.value.x;  // reverse X direction
            newPos.x = Clamp(newPos.x, 0, screenWidth);
        }
        if (newPos.y < 0 || newPos.y > screenHeight) {
            frontSensorDir.value.y = -frontSensorDir.value.y;  // reverse Y direction  
            newPos.y = Clamp(newPos.y, 0, screenHeight);
        }

        // update new position
        particlePos.value = newPos;
    };
};
