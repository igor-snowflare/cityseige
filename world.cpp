#include <iostream>
#include <cstdlib>
#include "config.hpp"
#include "world.hpp"

World::World(int x_size, int y_size) : x_size(x_size), y_size(y_size), blocks(x_size * y_size) {
	// Create a temporary corners vector for randomly generating elevation
	std::vector<float> corners((x_size + 1) * (y_size + 1));

	for (int y=0; y < y_size + 1; y++) {
		for (int x=0; x < x_size +1; x++) {
			corners[(y * x) + x] = static_cast<float>(rand() % max_elevation);
		}
	}

	// Need to set coordinates for each
	for (int y_pos=0; y_pos < y_size; y_pos++) {
		for (int x_pos=0; x_pos < x_size; x_pos++) {
			blocks[(y_pos * x_size) + x_pos].setCoordinates(x_pos, y_pos, corners);
		}
	}

	std::cout << "World generated!" << std::endl;
}

void World::render_world(SDL_Renderer* ren) {
	for (int y=0; y < y_size; y++) {
		for (int x=0; x < x_size; x++) {
			blocks[(y * x_size) + x].render(ren);
		}
	}
}