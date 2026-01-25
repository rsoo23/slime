// #include <entt.hpp>
// #include <Components.hpp>
// #include <raymath.h>
// #include <UniformGrid.hpp>

// void PheromoneLifetimeSystem(entt::registry& registry, float deltaTime, UniformGrid& pheromoneGrid) {
//     for (size_t i = 0; i < pheromoneGrid.cells.size(); ++i) {
//         if (pheromoneGrid.cells[i] <= 0) continue;

//         pheromoneGrid.cells[i] -= deltaTime;
//         if (pheromoneGrid.cells[i] < 0.f) {
//             pheromoneGrid.cells[i] = 0;
//         };
//     };
// }