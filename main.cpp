#include <iostream>
#include "config.hpp"
#include "world.cpp"
#include "game.cpp"

int world_size_x = 136;
int world_size_y = 78;

Game *game = nullptr;
Uint32 frameStart;
int last_update;

int main() {
	// Generate the random seed
	srand(time(0));

	// Generate the world
	World landscape = World(world_size_x, world_size_y);

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