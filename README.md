# Code Logic

1. init random amounts of slime particles (2D position + direction N, S, E, W) onto screen
2. init trail map
3. for each slime particle
    - check FL, F and FR for which direction has strongest pheromone value
    - if it has nothing then use same direction
    - assign new direction
    - move in new direction
    - add pheromone = 1 to trail map
4. for each pheromone particle
    - deplete by evaporation speed * delta time
    - set color based on this evaporation value
