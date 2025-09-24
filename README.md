# Citysiege — A C++ Simulation of Urban Warfare

The main purpose of this project is to further expand on the [Game of Life implementation](https://github.com/igor-snowflare/cpp_game_of_life), firstly in terms of optimization and secondly in terms of adding additional functionalities, and hopefully a higher level of interaction.

## How the World has changed

The biggest difference compared to the Game of Life implementation is that the `World` object is no longer relying on a two-dimensional array to construct the world grid, but rather a one-dimensional vector of `Block` objects which allows for using the heap, rather than stack memory. Furthermore, the use of one-dimensional datatype should ensure contiguous memory assignment, making the world grid much more cache-friendly and optimized.

In order to access individual blocks by their x, y coordinates the way that is intuitive (and also in a way that will be easily integrated into SDL3's rendering coordinate system), we calculate the position in the `blocks` vector using the following formula:

```
blocks[(y_pos * x_size) + x_pos]
```

The logic behind this is simple — if rows of the world are stored one after another, that means that for accessing a given row (being Y position, moving from top to bottom in SDL3's coordinate system) we need to take into account the number of all the rows that preceed it (`(y_pos * x_size)` with `x_size` refering to total size of the world) and then adding the desired `x_pos` in order to move from the beginning of the row to the right.