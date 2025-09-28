#include <iostream>
#include "config.hpp"
#include "world.cpp"
#include "game.cpp"
#include "river.cpp"

int world_size_x = 138;
int world_size_y = 78;

Game *game = nullptr;
Uint32 frameStart;
int last_update;

int main() {
	// Generate the random seed
	srand(time(0));

	// Generate the world
	World landscape = World(world_size_x, world_size_y);
	landscape.generate_terrain(primary_terrain_ratio, 1, false, 1);
	landscape.smooth_edges(primary_terrain_ratio);
	landscape.generate_terrain(secondary_terrain_ratio, 1, true, primary_impact);
	landscape.smooth_edges(secondary_terrain_ratio);
	landscape.generate_terrain(1, 1, true, secondary_impact);

	// Add a river
	int river_x_pos = rand() % world_size_x;
	River myRiver = River(river_x_pos, 0, landscape);

	// Start the game
	game = new Game();
	game->init("Test Game", world_size_x * block_size, world_size_y * block_size, false);

	// Main game loop
	while (game->running()) {
		frameStart = SDL_GetTicks();

		float elapsed = (static_cast<float>(frameStart) - static_cast<float>(last_update))/1000;
		
		game->handleEvents();
		game->update();
		game->render(&landscape);
	}
}