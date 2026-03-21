cmake_minimum_required(VERSION 3.23)
project(slime)

set(CMAKE_CXX_STANDARD 17)

# Download and build raylib automatically
include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG        5.5  # pin a specific version!
)
FetchContent_MakeAvailable(raylib)

add_executable(slime
    src/main.cpp
    src/Scene.cpp
    src/Timer.cpp
    src/UniformGrid.cpp
    src/systems/MovementSystem.cpp
    src/systems/PheromoneDepositSystem.cpp
    src/systems/PheromoneDiffusionSystem.cpp
    src/systems/RenderSystem.cpp
)

target_include_directories(slime PRIVATE
    includes
    includes/systems
    includes/components
)

target_link_libraries(slime PRIVATE raylib)