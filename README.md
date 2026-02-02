# Introduction

This project is a fun experiment allowing me to explore RayLib and Entity Component Systems using the entt library. Playing around with the configurations and logic also showed me how simple logic can create satisfying patterns that resemble what we can find in nature.

## Setup

## 1. Clone repository

```bash
git clone https://github.com/rsoo23/slime.git
```

## 2. Compile

### Linux

```bash
make PROJECT_NAME=slime
```

### Windows

```bash
mingw32-make PROJECT_NAME=slime
```

## 3. Run the program

```bash
./slime [pheromoneLifetime] [particleSpeed]
```

## Configuration

You can configure the settings for the program in `includes/Config.hpp`

## Showcase

### Slime Ring

Configuration:

```cpp
initType = InitType::CircleInwards
pheromoneLifetime = 2
particleSpeed = 10
...
```

<img width="773" height="783" alt="image" src="https://github.com/user-attachments/assets/e562be0b-0aa4-4550-88d6-64abad08275e" />

https://github.com/user-attachments/assets/31eb51aa-0e2c-4b0c-b0c6-5ebc58b7dce0

### Jellyfish Supernova

Configuration:

```cpp
initType = InitType::CircleInwards
pheromoneLifetime = 2
particleSpeed = 20
pheromoneColor = PURPLE
...
```

https://github.com/user-attachments/assets/46e5f422-1104-42e0-96db-42c0c36eda02

## High Level Logic

1. Initializes slime particles with a 2D position + direction onto screen (shape / number / randomness is based on initType)
2. Initializes an uniform 1D array that represents a pheromone grid
3. Every frame:
    - PheromoneDepositSystem (defines the pheromone depositing behaviour of the slime particles):
        - for each slime particle deposit a pheromone onto the grid

    - MovementSystem (defines the pheromone sampling and slime particle movement):
        - use Front Left (FL), Front (F) and Front Right (FR) sensors and sample the pheromone grid
        - compare sampled pheromone values
        - assign new direction to particle based on:
          - if F is stronger than FL and F then continue moving in the particle's initial direction
          - if F is weaker than FL and FR then move randomly left or right
          - if FL is stronger than FR then move a random angle to the left
          - if FR is stronger than FL then move a random angle to the right

    - PheromoneDiffusionSystem (defines the pheromone diffusion and evaporation behaviour):
        - all pheromone values are now averaged with their 8 surrounding grid cells to give a blurred effect, simulating diffusion
        - all pheromone values deplete over time, simulating evaporation

    - RenderSystem (defines the rendering system):
        - render all pheromones particles
        - render all slime particles

## References + Inspiration

- Sebastian Lague's Coding Adventure: Ant and Slime Simulations
  - <https://www.youtube.com/watch?v=X-iSQQgOd1A>

- Characteristics of pattern formation and evolution in approximations of physarum transport networks
  - <https://uwe-repository.worktribe.com/output/980579>
