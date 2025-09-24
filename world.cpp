#include <iostream>
#include "world.hpp"

World::World(int x_size, int y_size) : x_size(x_size), y_size(y_size), blocks(x_size * y_size) {
	// Need to set coordinates for each
	for (int y_pos=0; y_pos < y_size; y_pos++) {
		for (int x_pos=0; x_pos < x_size; x_pos++) {
			blocks[(y_pos * x_size) + x_pos].setCoordinates(x_pos, y_pos);
		}
	}

	std::cout << "World generated!" << std::endl;
}